#pragma once
#include <stdio.h>

#if defined(__cplusplus)
extern "C" {
#endif

FILE *fopen_utf8(const char *path, const char *mode);

#if defined(__cplusplus)
} // extern "C"
#endif
