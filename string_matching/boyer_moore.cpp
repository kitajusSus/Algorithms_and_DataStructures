#include "boyer_moore.h"
#include <array>
#include <algorithm>

namespace boyer_moore {
int search(const std::string &pattern, const std::string &text) {
    if (pattern.empty()) return 0;
    std::array<int, 256> bad;
    bad.fill(-1);
    for (size_t i = 0; i < pattern.size(); ++i) {
        bad[static_cast<unsigned char>(pattern[i])] = static_cast<int>(i);
    }
    size_t m = pattern.size();
    size_t n = text.size();
    size_t s = 0;
    while (s <= n - m) {
        int j = static_cast<int>(m - 1);
        while (j >= 0 && pattern[j] == text[s + j]) {
            --j;
        }
        if (j < 0) {
            return static_cast<int>(s);
        }
        unsigned char c = static_cast<unsigned char>(text[s + j]);
        int shift = std::max(1, j - bad[c]);
        s += shift;
    }
    return -1;
}
}

