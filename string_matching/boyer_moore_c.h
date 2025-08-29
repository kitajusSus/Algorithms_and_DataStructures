#ifndef BOYER_MOORE_C_H
#define BOYER_MOORE_C_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int boyer_moore_search(const char *pattern, const char *text);

#ifdef __cplusplus
}
#endif

#endif // BOYER_MOORE_C_H
