#include "unicodefile.h"
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <limits.h>
#include <errno.h>
#if defined(_WIN32)
#include <windows.h>
#endif

#if !defined(_WIN32)
FILE *fopen_utf8(const char *path, const char *mode)
{
    return fopen(path, mode);
}
#else
FILE *fopen_utf8(const char *path, const char *mode)
{
    size_t npath = strlen(path);
    size_t nmode = strlen(mode);
    wchar_t *wpath = NULL;
    wchar_t wmode[8];
    FILE *fh = NULL;

    if (npath > (size_t)INT_MAX || nmode > 7) {
        errno = EINVAL;
        goto end;
    }

    wpath = (wchar_t *)malloc((npath + 1) * sizeof(wchar_t));
    if (!wpath) {
        errno = ENOMEM;
        goto end;
    }

    if (!MultiByteToWideChar(CP_UTF8, 0, path, npath + 1, wpath, npath + 1) ||
        !MultiByteToWideChar(CP_UTF8, 0, mode, nmode + 1, wmode, nmode + 1))
    {
        errno = EINVAL;
        goto end;
    }

    fh = _wfopen(wpath, wmode);

end:
    if (wpath)
        free(wpath);
    return fh;
}
#endif
