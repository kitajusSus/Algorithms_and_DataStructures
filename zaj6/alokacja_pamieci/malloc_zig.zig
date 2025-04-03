const std = @import("std");

pub fn main() void {
    const allocator = std.heap.page_allocator;

    var arr = try allocator.alloc(u32, 5);
    defer allocator.free(arr);

    for (arr) |*item, index| {
        item.* = @intCast(u32, index + 1);
    }

    for (arr) |item| {
        std.debug.print("{} ", .{item});
    }
}