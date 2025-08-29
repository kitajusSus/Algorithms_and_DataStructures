#include "kmp_c.h"
#include <stdlib.h>
#include <string.h>

static void build_lps(const char *pattern, int *lps, size_t m) {
    size_t len = 0;
    lps[0] = 0;
    for (size_t i = 1; i < m;) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else if (len != 0) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }
}

int kmp_search(const char *pattern, const char *text) {
    size_t m = strlen(pattern);
    size_t n = strlen(text);
    if (m == 0) return 0;
    int *lps = (int*)malloc(sizeof(int) * m);
    if (!lps) return -1;
    build_lps(pattern, lps, m);
    size_t i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            ++i; ++j;
            if (j == m) {
                free(lps);
                return (int)(i - j);
            }
        } else if (j != 0) {
            j = lps[j - 1];
        } else {
            ++i;
        }
    }
    free(lps);
    return -1;
}

