const std = @import("std");

const MAX_SYMBOLS = 256;

const Node = struct {
    frequency: usize,
    symbol: ?u8,
    left: ?*Node,
    right: ?*Node,
};

fn allocNode(allocator: *std.mem.Allocator, frequency: usize, symbol: ?u8, left: ?*Node, right: ?*Node) !*Node {
    var node = try allocator.create(Node);
    node.* = Node{
        .frequency = frequency,
        .symbol = symbol,
        .left = left,
        .right = right,
    };
    return node;
}

fn countFrequencies(input: []const u8) [MAX_SYMBOLS]usize {
    var freq: [MAX_SYMBOLS]usize = undefined;
    freq.* = [_]usize{0} ** MAX_SYMBOLS;
    for (input) |c| {
        freq[c] += 1;
    }
    return freq;
}

fn buildHuffmanTree(
    allocator: *std.mem.Allocator,
    frequencies: [MAX_SYMBOLS]usize,
) !*Node {
    var list = std.ArrayList(*Node).init(allocator);

    // Initialize leaf nodes
    for (frequencies, 0..) |freq, symbol| {
        if (freq > 0) {
            const node = try allocNode(allocator, freq, @intCast(u8, symbol), null, null);
            try list.append(node);
        }
    }

    // Build tree
    while (list.items.len > 1) {
        // Find two nodes with lowest frequency
        std.sort.sort(*Node, list.items, {}, struct {
            pub fn lessThan(_: void, a: *Node, b: *Node) bool {
                return a.frequency < b.frequency;
            }
        }.lessThan);

        const left = list.items[0];
        const right = list.items[1];

        const merged = try allocNode(allocator, left.frequency + right.frequency, null, left, right);

        // Remove first two
        _ = list.orderedRemove(1);
        _ = list.orderedRemove(0);
        try list.append(merged);
    }

    return if (list.items.len != 0) list.items[0] else error.EmptyInput;
}

// Recursive function to build codes
fn buildCodes(
    node: *Node,
    code: []u8,
    depth: usize,
    codes: *[MAX_SYMBOLS][]u8,
    allocator: *std.mem.Allocator,
) !void {
    if (node.symbol) |sym| {
        // Leaf
        codes[sym] = try allocator.alloc(u8, depth);
        std.mem.copy(u8, codes[sym], code[0..depth]);
    } else {
        if (node.left) |left| {
            code[depth] = '0';
            try buildCodes(left, code, depth + 1, codes, allocator);
        }
        if (node.right) |right| {
            code[depth] = '1';
            try buildCodes(right, code, depth + 1, codes, allocator);
        }
    }
}

pub fn main() !void {
    const allocator = std.heap.page_allocator;
    const input = "zigzag huffman example";

    // Step 1: count frequencies
    const freq = countFrequencies(input);

    // Step 2: build Huffman tree
    var tree = try buildHuffmanTree(allocator, freq);

    // Step 3: build codes
    var codes: [MAX_SYMBOLS][]u8 = undefined;
    codes.* = [_][]u8{null} ** MAX_SYMBOLS;
    var tmp_code: [MAX_SYMBOLS]u8 = undefined;
    try buildCodes(tree, &tmp_code, 0, &codes, allocator);

    // Step 4: encode input
    var stdout = std.io.getStdOut().writer();
    try stdout.print("Symbol\tCode\n", .{});
    for (codes, 0..) |code, i| {
        if (code) |c| {
            try stdout.print("{c}\t{s}\n", .{ @intToEnum(u8, i), c });
        }
    }

    // Encode input string
    try stdout.print("\nEncoded: ", .{});
    for (input) |c| {
        try stdout.print("{s}", .{codes[c]});
    }
    try stdout.print("\n", .{});
}
