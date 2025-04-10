const std = @import("std");

pub fn main() !void {
    const allocator = std.heap.page_allocator;

    const arr = try allocator.alloc(u32, 5);
    defer allocator.free(arr);

    for (arr, 0..) |*item, index| {
        item.* = @intCast(index + 1);
    }

    for (arr) |item| {
        std.debug.print("{} ", .{item});
    }
    std.debug.print("\n", .{});
}
