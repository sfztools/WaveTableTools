#include "WaveFormula.h"
#include "Wavetable.h"
#include "dsp/Wavetables.h"
#include "utility/unicodefile.h"
#include "imgui.h"
#include "imgui_stdlib.h"
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
#include <vector>
#include <string>
#include <unordered_map>
#include <atomic>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static const char app_display_name[] = "WEdit";
static const ImVec2 window_size = ImVec2(864, 720);
static const int column1_width = 620;
static const int column2_width = 214;
static const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

static constexpr unsigned wave_size = 2048;
static constexpr unsigned max_wave_slots = 512;
static constexpr unsigned max_extent = 100;
static constexpr unsigned min_morph_size = 1;
static constexpr unsigned max_morph_size = 128;

static constexpr uint32_t extra_chunk_version = 0;
static constexpr char extra_chunk_id[] = "STws";

struct WaveGlobal {
    int morph_size = 64;
};

struct WaveSlot {
    struct Cache {
        WaveFormulaPtr formula;
    };

    mutable std::shared_ptr<Cache> cache;
    int seed = 0;
    int amptype = 1;
    int extent = 1;
    std::string expr = "x=1";

    void invalidate()
    {
        cache.reset();
    }

    const WaveFormula &formula() const
    {
        if (cache)
            return *cache->formula;
        cache.reset(new Cache);

        WaveFormulaPtr formula(new SeriesFormula(expr.c_str()));
        if (!formula->is_valid())
            formula.reset(new PartialsFormula(expr.c_str()));

        formula->set_size(wave_size);
        formula->set_seed(seed);
        formula->set_amplitude_type(static_cast<WaveFormula::AmplitudeType>(amptype));

        WaveFormula &ret = *formula;
        cache->formula = formula;
        return ret;
    }
};

struct SaveFileData {
    WaveGlobal global;
    const WaveSlot *slots = nullptr;
    unsigned num_slots = 0;
};

struct SaveFileBufferedData : SaveFileData {
    std::unique_ptr<WaveSlot[]> slots_buf;
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

// file dialog
static std::string last_file_dialog_dir;

static const float *get_plot_x(unsigned size);
static std::string choose_wavetable_path(bool save, std::string *dir);
static void save_wavetable(const WaveGlobal &global, const WaveSlot &slot, const std::string &path);
static void save_wavetable(const WaveGlobal &global, const WaveSlot slots[], unsigned slot_count, const std::string &path);
static std::string make_chunk(const SaveFileData& file_data);
static bool load_chunk(const char *filename, SaveFileBufferedData &file_data);
static bool load_chunk(FILE *fh, SaveFileBufferedData &file_data);
static void SDLCALL generate_audio(void *userdata, uint8_t *stream, int bytes);

extern "C" int utf8main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    WaveGlobal wave_global;
    std::unique_ptr<WaveSlot[]> wave_slots(new WaveSlot[max_wave_slots]);
    unsigned wave_slot_number = 0;
    unsigned used_wave_slots = 1;
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
    SDL_Window *window = SDL_CreateWindow(app_display_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)window_size.x, (int)window_size.y, window_flags);
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
    bool must_send_wave_later = true;
    bool must_send_wave_now = false;

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
                must_send_wave_now = true;
                break;
            }
        }

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        WaveSlot *current_wave_slot = &wave_slots[wave_slot_number];

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(column1_width, 0));
        if (ImGui::Begin("Create")) {
            if (ImGui::Button("Load wavetable")) {
                std::string file_path = choose_wavetable_path(false, &last_file_dialog_dir);
                if (!file_path.empty()) {
                    SaveFileBufferedData file_data;
                    if (!load_chunk(file_path.c_str(), file_data))
                        osdialog_message(OSDIALOG_WARNING, OSDIALOG_OK, "Could not load the wavetable file.");
                    else {
                        wave_global = file_data.global;
                        std::fill(&wave_slots[0], &wave_slots[used_wave_slots], WaveSlot());
                        used_wave_slots = std::min(file_data.num_slots, max_wave_slots);
                        for (unsigned i = 0; i < used_wave_slots; ++i)
                            wave_slots[i] = std::move(file_data.slots[i]);
                        wave_slot_number = 0;
                        current_wave_slot = &wave_slots[wave_slot_number];
                        must_send_wave_later = true;
                    }
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Save wavetable")) {
                std::string file_path = choose_wavetable_path(true, &last_file_dialog_dir);
                if (!file_path.empty())
                    save_wavetable(wave_global, wave_slots.get(), used_wave_slots, file_path);
            }
            ImGui::SameLine();
            if (ImGui::Button("Save single wave")) {
                std::string file_path = choose_wavetable_path(true, &last_file_dialog_dir);
                if (!file_path.empty())
                    save_wavetable(wave_global, *current_wave_slot, file_path);
            }
            ImGui::End();
        }

        ImGui::SetNextWindowPos(ImVec2(10, 80));
        ImGui::SetNextWindowSize(ImVec2(column1_width, 0));
        if (ImGui::Begin("Waveform")) {
            const float* x_data = nullptr;
            const float* y_data = nullptr;
            unsigned size = 0;

            const WaveFormula &formula = current_wave_slot->formula();
            if (formula.is_valid()) {
                size = wave_size;
                x_data = get_plot_x(size);
                y_data = formula.get_wave();
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
        ImGui::SetNextWindowSize(ImVec2(column1_width, 0));
        if (ImGui::Begin("Edit")) {
            ImGui::SetNextItemWidth(100);
            if (ImGui::InputInt("Seed", &current_wave_slot->seed)) {
                current_wave_slot->invalidate();
                must_send_wave_later = true;
            }
            ImGui::SameLine();

            ImGui::Spacing();
            ImGui::SameLine();

            const char *const items[] = {
                "Raw",
                "Normalized",
                "Saturated",
            };
            ImGui::SetNextItemWidth(100);
            if (ImGui::Combo("Amplitude", &current_wave_slot->amptype, items, IM_ARRAYSIZE(items))) {
                current_wave_slot->invalidate();
                must_send_wave_later = true;
            }

            if (ImGui::InputTextMultiline("Expression", &current_wave_slot->expr, ImVec2(0, 45))) {
                current_wave_slot->invalidate();
                must_send_wave_later = true;
            }

            ImGui::End();
        }

        ImGui::SetNextWindowPos(ImVec2(10, 655));
        ImGui::SetNextWindowSize(ImVec2(column1_width, 0));
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
                if (ImGui::ButtonEx(key_names[i], ImVec2((float)button_width, 0), ImGuiButtonFlags_PressedOnClick)) {
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

        ImGui::SetNextWindowPos(ImVec2(10 + column1_width + 10, 10));
        ImGui::SetNextWindowSize(ImVec2(column2_width, 700));
        if (ImGui::Begin("Morph")) {
            unsigned wave_slot_to_activate = ~0u;
            unsigned wave_slot_to_insert = ~0u;
            unsigned wave_slot_to_remove = ~0u;
            unsigned wave_slot_to_move_up = ~0u;
            unsigned wave_slot_to_move_down = ~0u;

            ImGui::SliderInt("Count", &wave_global.morph_size, min_morph_size, max_morph_size);
            ImGui::Separator();

            for (unsigned i = 0, n = used_wave_slots; i < n; ++i) {
                ImGui::PushID(i);

                char name[256];
                sprintf(name, "Slot %lu", (unsigned long)(i + 1));

                bool selected = (wave_slot_number == i);
                if (ImGui::Selectable(name, selected, 0, ImVec2(80, 0)))
                    wave_slot_to_activate = i;

                ImGui::SameLine();
                {
                    const float* y_data = nullptr;
                    unsigned size = 0;

                    const WaveFormula &formula = wave_slots[i].formula();
                    if (formula.is_valid()) {
                        size = wave_size;
                        y_data = formula.get_wave();
                    }

                    ImGui::PlotLines("", y_data, size, 0, "", -1.0f, +1.0f, ImVec2(40, 40));
                }

                ImGui::SameLine();
                ImGui::BeginChild("slot-controls-container-1", ImVec2(0, 42));
                ImGui::PushID("slot-add");
                if (ImGui::Button("+", ImVec2(20, 0)))
                    wave_slot_to_insert = i;
                ImGui::PopID();
                ImGui::SameLine();
                if (ImGui::ArrowButton("slot-move-up", ImGuiDir_Up))
                    wave_slot_to_move_up = i;
                ImGui::PushID("slot-delete");
                if (ImGui::Button("x", ImVec2(20, 0)))
                    wave_slot_to_remove = i;
                ImGui::PopID();
                ImGui::SameLine();
                if (ImGui::ArrowButton("slot-move-down", ImGuiDir_Down))
                    wave_slot_to_move_down = i;
                ImGui::EndChild();

                if (i + 1 != n) {
                    ImGui::BeginChild("slot-extent-container", ImVec2(0, 42));
                    ImGui::Indent();
                    ImGui::PushID("slot-extent");
                    ImGui::Separator();
                    ImGui::Text("Transition %d->%d", i + 1, i + 2);
                    ImGui::SetNextItemWidth(160);
                    ImGui::SliderInt("", &wave_slots[i].extent, 1, max_extent);
                    ImGui::PopID();
                    ImGui::EndChild();
                }

                ImGui::Separator();

                ImGui::PopID();
            }

            ImGui::End();

            if (wave_slot_to_activate != ~0u) {
                wave_slot_number = wave_slot_to_activate;
                current_wave_slot = &wave_slots[wave_slot_number];
                must_send_wave_later = true;
            }
            else if (wave_slot_to_insert != ~0u && used_wave_slots < max_wave_slots) {
                for (unsigned i = used_wave_slots; i-- > wave_slot_number; )
                    wave_slots[i + 1] = std::move(wave_slots[i]);
                ++used_wave_slots;
                wave_slots[wave_slot_number] = wave_slots[wave_slot_number + 1];
                ++wave_slot_number;
                current_wave_slot = &wave_slots[wave_slot_number];
                must_send_wave_later = true;
            }
            else if (wave_slot_to_remove != ~0u && used_wave_slots > 1) {
                for (unsigned i = wave_slot_number + 1; i < used_wave_slots; ++i)
                    wave_slots[i - 1] = std::move(wave_slots[i]);
                --used_wave_slots;
                wave_slot_number = std::min(wave_slot_number, used_wave_slots - 1);
                current_wave_slot = &wave_slots[wave_slot_number];
                must_send_wave_later = true;
            }
            else if (wave_slot_to_move_up != ~0u && wave_slot_to_move_up > 0) {
                unsigned a = wave_slot_to_move_up;
                unsigned b = wave_slot_to_move_up - 1;
                std::swap(wave_slots[a], wave_slots[b]);
                if (wave_slot_number == a || wave_slot_number == b)
                    must_send_wave_later = true;
            }
            else if (wave_slot_to_move_down != ~0u && wave_slot_to_move_down + 1 < used_wave_slots) {
                unsigned a = wave_slot_to_move_down;
                unsigned b = wave_slot_to_move_down + 1;
                std::swap(wave_slots[a], wave_slots[b]);
                if (wave_slot_number == a || wave_slot_number == b)
                    must_send_wave_later = true;
            }
        }

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);

        if (must_send_wave_later) {
            if (tm_send_wave)
                SDL_RemoveTimer(tm_send_wave);
            tm_send_wave = SDL_AddTimer(100, [](Uint32, void *) -> Uint32 {
                SDL_Event event = {};
                event.type = SDL_USEREVENT;
                SDL_PushEvent(&event);
                return 0;
            }, nullptr);

            must_send_wave_later = false;
        }

        if (must_send_wave_now) {
            sfz::WavetableMulti *wt = nullptr;
            const WaveFormula &formula = current_wave_slot->formula();
            if (formula.is_valid())
                wt = new sfz::WavetableMulti(sfz::Wavetables::createFromAudioData(formula.get_wave(), wave_size));

            SDL_LockAudioDevice(actx.dev);
            actx.wt.reset(wt);
            actx.osc.setWavetable(wt);
            SDL_UnlockAudioDevice(actx.dev);

            must_send_wave_now = false;
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

static const float *get_plot_x(unsigned size)
{
    if (size == 0)
        return nullptr;

    static std::unordered_map<unsigned, std::unique_ptr<float[]>> assoc;

    auto it = assoc.find(size);
    if (it != assoc.end())
        return it->second.get();

    float *x_data = new float[size];
    for (unsigned i = 0; i < size; ++i)
        x_data[i] = i * (1.0f / size);

    assoc[size] = std::unique_ptr<float[]>(x_data);
    return x_data;
}

static std::string choose_wavetable_path(bool save, std::string *dir)
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

    const char *default_path = nullptr;
    if (dir && !dir->empty())
        default_path = dir->c_str();

    char *osdialog_ret = osdialog_file(
        save ? OSDIALOG_SAVE : OSDIALOG_OPEN, default_path, nullptr, filters);
    if (!osdialog_ret)
        return std::string();

    std::string path(osdialog_ret);
    free(osdialog_ret);

    if (save && path.find_last_of('.') == path.npos) {
        path += ".wav";
        if (FILE *fh = fopen_utf8(path.c_str(), "rb")) {
            free(fh);
            if (osdialog_message(OSDIALOG_INFO, OSDIALOG_YES_NO, "The file already exists. Do you want to replace it?") != 1)
                return std::string();
        }
    }

    if (dir) {
#if !defined(_WIN32)
        size_t dirlen = path.find_last_of('/');
#else
        size_t dirlen = path.find_last_of("/\\");
#endif
        if (dirlen != path.npos) {
            ++dirlen;
            *dir = path.substr(0, dirlen);
        }
    }

    return path;
}

static void save_wavetable(const WaveGlobal &global, const WaveSlot &slot, const std::string &path)
{
    const WaveFormula &formula = slot.formula();
    const unsigned frames = ::wave_size;
    assert(frames == formula.get_size());

    Wavetable wt;
    wt.count = 1;
    wt.frames = frames;
    wt.data.reset(new float[frames]);

    if (!formula.is_valid())
        std::fill(&wt.data[0], &wt.data[frames], 0.0f);
    else {
        const float *wave = formula.get_wave();
        std::copy(wave, wave + frames, wt.data.get());
    }

    //
    SaveFileData file_data;
    file_data.global = global;
    file_data.slots = &slot;
    file_data.num_slots = 1;
    const std::string chunk = make_chunk(file_data);

    FILE *fh = fopen_utf8(path.c_str(), "wb");
    if (fh) {
        Wavetables::saveToWAVFile(fh, wt, extra_chunk_id, chunk.data(), chunk.size());
        fclose(fh);
    }
}

static void save_wavetable(const WaveGlobal &global, const WaveSlot slots[], unsigned slot_count, const std::string &path)
{
    const unsigned frames = ::wave_size;
    const unsigned morph_size = global.morph_size;

    Wavetable wt;
    wt.count = morph_size;
    wt.frames = frames;
    wt.data.reset(new float[morph_size * frames]);

    //
    unsigned total_extent = 0;
    for (unsigned i = 0; i < slot_count - 1; ++i)
        total_extent += slots[i].extent;

    //
    std::unique_ptr<float[]> slot_morph_pos(new float[slot_count]);
    for (unsigned i = 0, sum = 0; i < slot_count; ++i) {
        slot_morph_pos[i] = sum / float(total_extent);
        sum += slots[i].extent;
    }

    //
    for (unsigned m = 0; m < morph_size; ++m) {
        const float morph_pos = m / float(morph_size - 1);

        unsigned j1 = 0;
        for (; j1 + 1 < slot_count && morph_pos > slot_morph_pos[j1 + 1]; ++j1);
        unsigned j2 = std::min(j1 + 1, slot_count - 1);
        float mu = (morph_pos - slot_morph_pos[j1]) / (slot_morph_pos[j2] - slot_morph_pos[j1]);

        float *dst = &wt.data[m * frames];
        std::fill(&dst[0], &dst[frames], 0.0f);

        const WaveFormula &f1 = slots[j1].formula();
        assert(frames == f1.get_size());
        if (f1.is_valid()) {
            const float *w1 = f1.get_wave();
            for (unsigned i = 0; i < frames; ++i)
                dst[i] += (1 - mu) * w1[i];
        }

        const WaveFormula &f2 = slots[j2].formula();
        assert(frames == f2.get_size());
        if (f2.is_valid()) {
            const float *w2 = f2.get_wave();
            for (unsigned i = 0; i < frames; ++i)
                dst[i] += mu * w2[i];
        }
    }

    //
    SaveFileData file_data;
    file_data.global = global;
    file_data.slots = slots;
    file_data.num_slots = slot_count;
    const std::string chunk = make_chunk(file_data);

    FILE *fh = fopen_utf8(path.c_str(), "wb");
    if (fh) {
        Wavetables::saveToWAVFile(fh, wt, extra_chunk_id, chunk.data(), chunk.size());
        fclose(fh);
    }
}

///
template <class T> static void to_little_endian(T src, void *dst)
{
    typedef typename std::make_unsigned<T>::type U;
    for (size_t i = 0; i < sizeof(T); ++i)
        ((uint8_t *)dst)[i] = uint8_t(U(src) >> (8 * i));
}

template <class T> static void from_little_endian(const void *src, T &dst)
{
    typedef typename std::make_unsigned<T>::type U;
    U val = 0;
    for (size_t i = 0; i < sizeof(T); ++i)
        val |= ((const uint8_t *)src)[i] << (8 * i);
    dst = val;
}

///
static std::string make_chunk(const SaveFileData& file_data)
{
    std::string chunk;
    chunk.reserve(64 * 1024);

    const WaveSlot *slots = file_data.slots;
    unsigned num_slots = file_data.num_slots;

    auto write_u32 = [&chunk](uint32_t x) {
        char b[4];
        to_little_endian(x, b);
        chunk.append(b, 4);
    };
    auto write_str = [&chunk](const std::string &s) {
        chunk.append(s);
        chunk.push_back('\0');
    };

    write_u32(extra_chunk_version);
    write_u32(file_data.global.morph_size);
    write_u32(num_slots);
    for (unsigned i = 0; i < num_slots; ++i) {
        const WaveSlot &slot = slots[i];
        write_u32(slot.seed);
        write_u32(slot.amptype);
        write_u32(slot.extent);
        write_str(slot.expr);
    }

    return chunk;
}

static bool load_chunk(const char *filename, SaveFileBufferedData &file_data)
{
    FILE *fh = fopen_utf8(filename, "rb");
    if (!fh)
        return false;
    bool ret = load_chunk(fh, file_data);
    fclose(fh);
    return ret;
}

static bool load_chunk(FILE *fh, SaveFileBufferedData &file_data)
{
    char magic[4];

    auto fread_u32 = [fh](uint32_t &x) -> bool {
        uint8_t b[4];
        if (fread(b, 1, 4, fh) != 4)
            return false;
        from_little_endian(b, x);
        return true;
    };

    if (fread(magic, 1, 4, fh) != 4 || memcmp(magic, "RIFF", 4) ||
        fseek(fh, 4, SEEK_CUR) != 0 ||
        fread(magic, 1, 4, fh) != 4 || memcmp(magic, "WAVE", 4))
    {
        return false;
    }

    while (fread(magic, 1, 4, fh) == 4 && memcmp(magic, extra_chunk_id, 4)) {
        uint32_t size;
        if (!fread_u32(size) || fseek(fh, size, SEEK_CUR) != 0)
            return false;
    }

    if (memcmp(magic, extra_chunk_id, 4))
        return false;

    file_data = SaveFileBufferedData();

    uint32_t size;
    if (!fread_u32(size))
        return false;

    std::unique_ptr<uint8_t[]> data(new uint8_t[size]);
    if (fread(data.get(), 1, size, fh) != size)
        return false;

    //
    const uint8_t *data_ptr = data.get();
    uint32_t data_avail = size;

    auto read_u32 = [&data_ptr, &data_avail](uint32_t &x) -> bool {
        if (data_avail < 4)
            return false;
        from_little_endian(data_ptr, x);
        data_ptr += 4;
        data_avail -= 4;
        return true;
    };
    auto read_str = [&data_ptr, &data_avail](std::string &x) -> bool {
        const char *endp = (const char *)memchr(data_ptr, '\0', data_avail);
        if (!endp)
            return false;
        size_t length = (const uint8_t *)endp - data_ptr;
        x.assign((const char *)data_ptr, length);
        data_ptr += length + 1;
        data_avail -= length + 1;
        return true;
    };

    //
    uint32_t version;
    if (!read_u32(version) || version != 0)
        return false;

    uint32_t morph_size;
    if (!read_u32(morph_size))
        return false;

    morph_size = std::max(min_morph_size, std::min(max_morph_size, morph_size));
    file_data.global.morph_size = morph_size;

    uint32_t num_slots;
    if (!read_u32(num_slots) || num_slots < 1)
        return false;

    WaveSlot *slots = new WaveSlot[num_slots];
    file_data.slots = slots;
    file_data.slots_buf.reset(slots);
    file_data.num_slots = num_slots;

    for (uint32_t i = 0; i < num_slots; ++i) {
        uint32_t seed, amptype, extent;
        if (!read_u32(seed) || !read_u32(amptype) || !read_u32(extent))
            return false;

        extent = std::max(1u, std::min(max_extent, extent));

        slots[i].seed = seed;
        slots[i].amptype = amptype;
        slots[i].extent = extent;

        if (!read_str(slots[i].expr))
            return false;
    }

    return true;
}

static void SDLCALL generate_audio(void *userdata, uint8_t *stream, int bytes)
{
    AudioContext *actx = (AudioContext *)userdata;
    const float srate = (float)actx->spec.freq;
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
