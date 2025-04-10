const std = @import("std");

fn triangle(n: i32) i32 {
    if (n == 1) {
        return 1;
    } else {
        return n + triangle(n - 1);
    }
}

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();
    const stdin = std.io.getStdIn().reader();

    try stdout.print("enter a number: ", .{});

    var buffer: [100]u8 = undefined;
    if (try stdin.readUntilDelimiterOrEof(&buffer, '\n')) |input| {
        // Trim any whitespace or newline characters
        const trimmed = std.mem.trim(u8, input, &std.ascii.whitespace);
        if (trimmed.len == 0) {
            try stdout.print("Error: Empty input\n", .{});
            return;
        }

        // Parse the integer, handling potential errors
        const number = std.fmt.parseInt(i32, trimmed, 10) catch |err| {
            try stdout.print("Error parsing number: {}\n", .{err});
            return;
        };

        // Start timing
        var timer = try std.time.Timer.start();
        const start = timer.read();

        const result = triangle(number);

        // End timing
        const end = timer.read();
        const duration = end - start;
        const duration_ms = @as(f64, @floatFromInt(duration)) / 1_000_000.0;

        try stdout.print("Triangle= {}\n", .{result});
        try stdout.print("Time taken: {d:.6} ms\n", .{duration_ms});
    } else {
        try stdout.print("Error: No input received\n", .{});
    }
}
