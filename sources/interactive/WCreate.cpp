#include "WaveFormula.h"
#include "Wavetable.h"
#include "dsp/Wavetables.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "implot.h"
#include "osdialog.h"
#include <SDL.h>
#include <SDL_opengl.h>
#if !defined(_WIN32) && !defined(__APPLE__)
#include <gtk/gtk.h>
#endif
#include <string>
#include <atomic>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>

static const char app_display_name[] = "WCreate";
static const ImVec2 window_size = ImVec2(640, 720);
static const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

static const unsigned wave_size = 2048;

struct CreateParam {
    bool need_update = false;
    WaveFormulaPtr formula;
    int seed = 0;
    int amptype = 1;
    char expr[1024] = "x=1";
};

enum class AudioRequest : int {
    none,
    key,
};

struct AudioContext {
    SDL_AudioSpec spec {};
    SDL_AudioDeviceID dev = 0;

    // synth info
    bool key_on = false;
    float eg = 0.0f;
    float eg_time = 0.0f;
    float gain = 0.25f;
    float attack = 0.01f;
    float release = 0.1f;
    float release_at = 1.0f;
    float pitch = 0.0f;
    sfz::WavetableOscillator osc;
    std::unique_ptr<sfz::WavetableMulti> wt;
    std::vector<float> buf;

    // communication
    std::atomic<AudioRequest> request { AudioRequest::none };
    union {
        float pitch;
        float wave[wave_size];
    } send;
};

static WaveFormulaPtr create_formula(const char* expr);
static std::string get_save_path();
static void save_wavetable(const WaveFormula &formula, const std::string &path);
static void SDLCALL generate_audio(void *userdata, uint8_t *stream, int bytes);

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    CreateParam param;
    param.need_update = true;
    int play_octave = 4;
    int play_key = 0;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }

#if !defined(_WIN32) && !defined(__APPLE__)
    gtk_init(nullptr, nullptr);
#endif

    //
    AudioContext actx;
    actx.spec.freq = 44100;
    actx.spec.format = AUDIO_F32SYS;
    actx.spec.channels = 2;
    actx.spec.samples = 512;
    actx.spec.callback = &generate_audio;
    actx.spec.userdata = &actx;

    actx.dev = SDL_OpenAudioDevice(
        nullptr, false, &actx.spec, &actx.spec,
        SDL_AUDIO_ALLOW_FREQUENCY_CHANGE|SDL_AUDIO_ALLOW_SAMPLES_CHANGE);

    if (actx.dev == 0) {
        osdialog_message(OSDIALOG_ERROR, OSDIALOG_OK, "Error: could not open the audio device.");
        return 1;
    }

    actx.osc.init(actx.spec.freq);
    actx.buf.resize(actx.spec.samples);

    SDL_PauseAudioDevice(actx.dev, false);

    //
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window *window = SDL_CreateWindow(app_display_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_size.x, window_size.y, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = nullptr;

    ImGui::StyleColorsClassic();

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

    //
    SDL_TimerID tm_send_wave = 0;
    bool must_send_wave = false;

    //
    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                    done = true;
                break;
            case SDL_USEREVENT:
                must_send_wave = true;
                break;
            }
        }

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(window_size.x - 20, 0));
        if (ImGui::Begin("Create")) {
            if (ImGui::Button("Save waveform")) {
                std::string file_path = get_save_path();
                if (!file_path.empty())
                    save_wavetable(*param.formula, file_path);
            }
            ImGui::End();
        }

        ImGui::SetNextWindowPos(ImVec2(10, 80));
        ImGui::SetNextWindowSize(ImVec2(window_size.x - 20, 0));
        if (ImGui::Begin("Waveform")) {
            float* x_data = nullptr;
            const float* y_data = nullptr;
            unsigned size = 0;

            if (param.formula && param.formula->is_valid()) {
                y_data = param.formula->get_wave();
                size = wave_size;
            }

            std::unique_ptr<float[]> x_buf;
            if (size > 0) {
                x_data = new float[size];
                x_buf.reset(x_data);
                for (unsigned i = 0; i < size; ++i)
                    x_data[i] = i * (1.0f / size);
            }

            ImPlot::SetNextPlotLimitsX(0.0, 1.0);
            ImPlot::SetNextPlotLimitsY(-1.01, +1.01);

            if (ImPlot::BeginPlot(
                    "", "", "", ImVec2(-1, 410),
                    ImPlotFlags_AntiAliased|ImPlotFlags_Crosshairs,
                    ImPlotAxisFlags_None,
                    ImPlotAxisFlags_None))
            {
                ImPlot::PlotLine("", x_data, y_data, size);
                ImPlot::EndPlot();
            }

            ImGui::End();
        }

        ImGui::SetNextWindowPos(ImVec2(10, 540));
        ImGui::SetNextWindowSize(ImVec2(window_size.x - 20, 0));
        if (ImGui::Begin("Edit")) {
            ImGui::SetNextItemWidth(100);
            if (ImGui::InputInt("Seed", &param.seed))
                param.need_update = true;
            ImGui::SameLine();

            ImGui::Spacing();
            ImGui::SameLine();

            const char *const items[] = {
                "Raw",
                "Normalized",
                "Saturated",
            };
            ImGui::SetNextItemWidth(100);
            if (ImGui::Combo("Amplitude", &param.amptype, items, IM_ARRAYSIZE(items)))
                param.need_update = true;

            if (ImGui::InputTextMultiline("Expression", param.expr, IM_ARRAYSIZE(param.expr), ImVec2(0, 45)))
                param.need_update = true;

            ImGui::End();
        }

        ImGui::SetNextWindowPos(ImVec2(10, 655));
        ImGui::SetNextWindowSize(ImVec2(window_size.x - 20, 0));
        if (ImGui::Begin("Play")) {
            const char *key_names[] = {
                "C", "C#", "D", "D#", "E",
                "F", "F#", "G", "G#",  "A", "A#", "B",
            };

            bool key_played = false;

            for (unsigned i = 0, n = IM_ARRAYSIZE(key_names); i < n; ++i) {
                int button_width = 25;
                if (i > 0)
                    ImGui::SameLine(ImGui::GetWindowContentRegionMin().x + i * button_width);
                if (ImGui::ButtonEx(key_names[i], ImVec2(button_width, 0), ImGuiButtonFlags_PressedOnClick)) {
                    play_key = i;
                    key_played = true;
                }
            }

            ImGui::SameLine();
            ImGui::Spacing();
            ImGui::SameLine();
            ImGui::SetNextItemWidth(240);
            ImGui::SliderInt("Octave", &play_octave, -1, 10, "%d");

            if (key_played) {
                const int note = 12 * (play_octave + 1) + play_key;
                const float pitch = 440.0f * std::exp2((note - 69.0f) * (float)(1.0f / 12.0f));
                actx.send.pitch = pitch;
                actx.request.store(AudioRequest::key);
                while (actx.request.load() != AudioRequest::none)
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }

            ImGui::End();
        }

        if (param.need_update) {
            WaveFormulaPtr formula(create_formula(param.expr));
            param.formula = formula;

            if (formula) {
                formula->set_size(wave_size);
                formula->set_seed(param.seed);
                formula->set_amplitude_type(static_cast<WaveFormula::AmplitudeType>(param.amptype));

                if (tm_send_wave)
                    SDL_RemoveTimer(tm_send_wave);
                tm_send_wave = SDL_AddTimer(100, [](Uint32, void *) -> Uint32 {
                    SDL_Event event = {};
                    event.type = SDL_USEREVENT;
                    SDL_PushEvent(&event);
                    return 0;
                }, nullptr);
            }

            param.need_update = false;
        }

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);

        if (must_send_wave) {
            sfz::WavetableMulti *wt = nullptr;
            if (param.formula)
                wt = new sfz::WavetableMulti(sfz::Wavetables::createFromAudioData(param.formula->get_wave(), wave_size));
            actx.wt.reset(wt);

            SDL_LockAudioDevice(actx.dev);
            actx.osc.setWavetable(wt);
            SDL_UnlockAudioDevice(actx.dev);

            must_send_wave = false;
        }
    }

    SDL_CloseAudioDevice(actx.dev);

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

static WaveFormulaPtr create_formula(const char* expr)
{
    WaveFormulaPtr formula;

    if (!formula) {
        formula.reset(new SeriesFormula(expr));
        if (!formula->is_valid())
            formula.reset();
    }

    if (!formula) {
        formula.reset(new PartialsFormula(expr));
        if (!formula->is_valid())
            formula.reset();
    }

    return formula;
}

static std::string get_save_path()
{
    osdialog_filter_patterns patterns[] = {
        { const_cast<char *>("wav"), nullptr },
    };
    osdialog_filters filters[] = {
        { const_cast<char *>("Wavetable files"), patterns, nullptr },
    };

    for (size_t i = 1; i < IM_ARRAYSIZE(patterns); ++i)
        patterns[i - 1].next = &patterns[i];
    for (size_t i = 1; i < IM_ARRAYSIZE(filters); ++i)
        filters[i - 1].next = &filters[i];

    char *osdialog_ret = osdialog_file(
        OSDIALOG_SAVE, nullptr, nullptr, filters);
    if (!osdialog_ret)
        return std::string();

    std::string path(osdialog_ret);
    free(osdialog_ret);
    return path;
}

static void save_wavetable(const WaveFormula &formula, const std::string &path)
{
    float *wave = formula.get_wave();
    unsigned frames = formula.get_size();

    Wavetable wt;
    wt.count = 1;
    wt.frames = frames;
    wt.data.reset(new float[frames]);

    std::copy(wave, wave + frames, wt.data.get());

    FILE *fh = fopen(path.c_str(), "wb");
    if (fh) {
        Wavetables::saveToWAVFile(fh, wt);
        fclose(fh);
    }
}

static void SDLCALL generate_audio(void *userdata, uint8_t *stream, int bytes)
{
    AudioContext *actx = (AudioContext *)userdata;
    const float srate = actx->spec.freq;
    const float speriod = 1.0f / srate;
    float *outputs = (float *)stream;
    const unsigned nframes = (unsigned)bytes / (2 * sizeof(float));

    //
    AudioRequest req = actx->request.load();
    switch (req) {
    default:
        assert(false);
        break;
    case AudioRequest::none:
        break;
    case AudioRequest::key:
        actx->key_on = true;
        actx->eg_time = 0;
        actx->pitch = actx->send.pitch;
        break;
    }
    actx->request.store(AudioRequest::none);

    //
    float eg = actx->eg;
    float eg_time = actx->eg_time;
    const float gain = actx->gain;
    const bool key_on = actx->key_on;

    const float pitch = actx->pitch;
    const float eg_attack_step = speriod / actx->attack;
    const float eg_release_step = speriod / -actx->release;
    const float release_at = actx->release_at;

    sfz::WavetableOscillator &osc = actx->osc;
    std::vector<float> &buf = actx->buf;

    if (buf.size() < nframes)
        buf.resize(nframes);

    float *osc_output = buf.data();
    osc.process(pitch, 1.0f, osc_output, nframes);

    for (unsigned i = 0; i < nframes; ++i) {
        const float out = osc_output[i] * gain * eg;
        outputs[2 * i] = out;
        outputs[2 * i + 1] = out;

        const bool releasing = !key_on || eg_time > release_at;
        const float eg_step = releasing ? eg_release_step : eg_attack_step;

        eg = std::min(1.0f, std::max(0.0f, eg + eg_step));
        eg_time += speriod;
    }

    actx->eg = eg;
    actx->eg_time = eg_time;
}
