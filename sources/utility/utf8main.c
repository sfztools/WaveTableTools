#if defined(_WIN32)
#include <windows.h>
#include <stdlib.h>
#endif

int utf8main(int argc, char *argv[]);

#if !defined(_WIN32)
int main(int argc, char *argv[])
{
    return utf8main(argc, argv);
}
#else
int WINAPI wWinMain(
    HINSTANCE instance, HINSTANCE prev_instance, PWSTR cmd_line, int cmd_show)
{
    int ret = 1;
    unsigned argc = __argc;
    wchar_t **wide_argv = __wargv;
    char **utf8_argv;
    unsigned count;
    unsigned i;

    (void)instance;
    (void)prev_instance;
    (void)cmd_line;
    (void)cmd_show;

    utf8_argv = calloc(argc + 1, sizeof(char *));
    if (!utf8_argv)
        goto end;

    for (i = 0; i < argc; ++i) {
        count = WideCharToMultiByte(CP_UTF8, 0, wide_argv[i], -1, NULL, 0, NULL, NULL);
        if (count == 0)
            goto end;
        utf8_argv[i] = malloc(count);
        if (!utf8_argv[i])
            goto end;
        if ((unsigned)WideCharToMultiByte(CP_UTF8, 0, wide_argv[i], -1, utf8_argv[i], count, NULL, NULL) != count)
            goto end;
    }

    ret = utf8main(argc, utf8_argv);

end:
    if (utf8_argv) {
        for (i = 0; i < argc; ++i)
            free(utf8_argv[i]);
        free(utf8_argv);
    }
    return ret;
}
#endif
