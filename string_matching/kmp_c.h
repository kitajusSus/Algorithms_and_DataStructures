#ifndef KMP_C_H
#define KMP_C_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int kmp_search(const char *pattern, const char *text);

#ifdef __cplusplus
}
#endif

#endif // KMP_C_H
