const std = @import("std");

pub fn search(pattern: []const u8, text: []const u8) ?usize {
    if (pattern.len == 0) return 0;
    if (pattern.len > text.len) return null;
    var bad: [256]isize = undefined;
    for (bad) |*b| b.* = -1;
    var i: usize = 0;
    while (i < pattern.len) : (i += 1) {
        bad[pattern[i]] = @as(isize, @intCast(i));
    }
    var s: usize = 0;
    while (s + pattern.len <= text.len) {
        var j: isize = @as(isize, @intCast(pattern.len)) - 1;
        while (j >= 0 and pattern[@as(usize, @intCast(j))] == text[s + @as(usize, @intCast(j))]) {
            j -= 1;
        }
        if (j < 0) return s;
        const c = text[s + @as(usize, @intCast(j))];
        var shift: isize = j - bad[c];
        if (shift < 1) shift = 1;
        s += @as(usize, @intCast(shift));
    }
    return null;
}
