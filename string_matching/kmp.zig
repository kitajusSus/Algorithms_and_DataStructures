const std = @import("std");

pub fn search(pattern: []const u8, text: []const u8) ?usize {
    if (pattern.len == 0) return 0;
    var allocator = std.heap.page_allocator;
    var lps = allocator.alloc(usize, pattern.len) catch return null;
    defer allocator.free(lps);

    var len: usize = 0;
    lps[0] = 0;
    var i: usize = 1;
    while (i < pattern.len) {
        if (pattern[i] == pattern[len]) {
            len += 1;
            lps[i] = len;
            i += 1;
        } else if (len != 0) {
            len = lps[len - 1];
        } else {
            lps[i] = 0;
            i += 1;
        }
    }

    var ti: usize = 0;
    var pj: usize = 0;
    while (ti < text.len) {
        if (pattern[pj] == text[ti]) {
            ti += 1;
            pj += 1;
            if (pj == pattern.len) return ti - pj;
        } else if (pj != 0) {
            pj = lps[pj - 1];
        } else {
            ti += 1;
        }
    }
    return null;
}
