#include "boyer_moore_c.h"
#include <string.h>

int boyer_moore_search(const char *pattern, const char *text) {
    size_t m = strlen(pattern);
    size_t n = strlen(text);
    if (m == 0) return 0;
    int bad[256];
    for (int i = 0; i < 256; ++i) bad[i] = -1;
    for (size_t i = 0; i < m; ++i) bad[(unsigned char)pattern[i]] = (int)i;
    size_t s = 0;
    while (s <= n - m) {
        int j = (int)m - 1;
        while (j >= 0 && pattern[j] == text[s + j]) --j;
        if (j < 0) return (int)s;
        unsigned char c = (unsigned char)text[s + j];
        int shift = j - bad[c];
        if (shift < 1) shift = 1;
        s += shift;
    }
    return -1;
}
