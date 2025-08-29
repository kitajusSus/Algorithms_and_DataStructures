#include "kmp.h"
#include <vector>

namespace kmp {
namespace {
std::vector<int> buildLPS(const std::string &pattern) {
    std::vector<int> lps(pattern.size());
    int len = 0;
    lps[0] = 0;
    for (size_t i = 1; i < pattern.size(); ) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else if (len != 0) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}
}

int search(const std::string &pattern, const std::string &text) {
    if (pattern.empty()) return 0;
    auto lps = buildLPS(pattern);
    size_t i = 0; // index for text
    size_t j = 0; // index for pattern
    while (i < text.size()) {
        if (pattern[j] == text[i]) {
            ++i;
            ++j;
            if (j == pattern.size()) {
                return static_cast<int>(i - j);
            }
        } else if (j != 0) {
            j = lps[j - 1];
        } else {
            ++i;
        }
    }
    return -1;
}
}

