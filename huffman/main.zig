const std = @import("std");
const Allocator = std.mem.Allocator;
const ArrayList = std.ArrayList;
const HashMap = std.HashMap;

// Struktura węzła w drzewie Huffmana
const Node = struct {
    char: ?u8, // Znak (tylko dla liści)
    freq: usize, // Częstotliwość
    left: ?*Node, // Lewe dziecko
    right: ?*Node, // Prawe dziecko

    fn isLeaf(self: Node) bool {
        return self.left == null and self.right == null;
    }
};

// Funkcja do porównywania węzłów (dla sortowania w kolejce priorytetowej)
fn nodeCompare(_: void, a: *Node, b: *Node) std.math.Order {
    return std.math.order(a.freq, b.freq);
}

// 1. Oblicz częstotliwość znaków
fn calculateFrequencies(text: []const u8, allocator: Allocator) !HashMap(u8, usize, std.hash_map.AutoContext(u8), std.hash_map.default_max_load_percentage) {
    var freq_map = HashMap(u8, usize, std.hash_map.AutoContext(u8), std.hash_map.default_max_load_percentage).init(allocator);
    errdefer freq_map.deinit();

    for (text) |char| {
        const count = freq_map.get(char) orelse 0;
        try freq_map.put(char, count + 1);
    }
    return freq_map;
}

// 2. & 3. Zbuduj drzewo Huffmana
fn buildHuffmanTree(freq_map: *const HashMap(u8, usize, std.hash_map.AutoContext(u8), std.hash_map.default_max_load_percentage), allocator: Allocator) !?*Node {
    var nodes = ArrayList(*Node).init(allocator);
    defer {
        // Uwaga: Drzewo jest zbudowane, węzły są połączone.
        // Jeśli korzeń zostanie zwolniony rekurencyjnie, nie zwalniaj tutaj.
        // Jeśli nie, to trzeba posprzątać wszystkie węzły.
        // Dla tego przykładu, zakładamy, że korzeń będzie zarządzany/zwolniony później.
        // nodes.deinit(); // Zależy od strategii zarządzania pamięcią węzłów.
    }

    var it = freq_map.iterator();
    while (it.next()) |entry| {
        const node = try allocator.create(Node);
        node.* = .{
            .char = entry.key_ptr.*,
            .freq = entry.value_ptr.*,
            .left = null,
            .right = null,
        };
        try nodes.append(node);
    }

    if (nodes.items.len == 0) {
        return null;
    }
    if (nodes.items.len == 1) { // Obsługa przypadku z jednym unikalnym znakiem
        const leaf = nodes.items[0];
        const root = try allocator.create(Node);
        root.* = .{ .char = null, .freq = leaf.freq, .left = leaf, .right = null };
        nodes.deinit(); // zwolnij listę, nie węzły
        return root;
    }

    while (nodes.items.len > 1) {
        // Sortuj, aby symulować kolejkę priorytetową (min-heap)
        std.sort.block(*Node, nodes.items, {}, nodeCompare);

        const left = nodes.orderedRemove(0);
        const right = nodes.orderedRemove(0);

        const parent = try allocator.create(Node);
        parent.* = .{
            .char = null,
            .freq = left.freq + right.freq,
            .left = left,
            .right = right,
        };
        try nodes.append(parent);
    }

    const root = nodes.items[0];
    nodes.deinit(); // zwolnij listę, nie węzły
    return root;
}

// 4. Wygeneruj kody Huffmana
fn generateCodesRecursive(
    node: ?*Node,
    current_code: *ArrayList(u8),
    codes_map: *HashMap(u8, []const u8, std.hash_map.AutoContext(u8), std.hash_map.default_max_load_percentage),
    allocator: Allocator,
) !void {
    if (node) |n| {
        if (n.isLeaf()) {
            if (n.char) |char_val| {
                const code_slice = try allocator.dupe(u8, current_code.items);
                //std.debug.print("Char: {c}, Code: {s}\n", .{ char_val, code_slice });
                try codes_map.put(char_val, code_slice);
            }
        } else {
            try current_code.append('0');
            try generateCodesRecursive(n.left, current_code, codes_map, allocator);
            _ = current_code.pop();

            try current_code.append('1');
            try generateCodesRecursive(n.right, current_code, codes_map, allocator);
            _ = current_code.pop();
        }
    }
}

fn generateCodes(
    root_node: ?*Node,
    allocator: Allocator,
) !HashMap(u8, []const u8, std.hash_map.AutoContext(u8), std.hash_map.default_max_load_percentage) {
    var codes_map = HashMap(u8, []const u8, std.hash_map.AutoContext(u8), std.hash_map.default_max_load_percentage).init(allocator);
    // Nie robimy defer deinit dla codes_map, bo chcemy ją zwrócić.
    // Kody ([]const u8) wewnątrz mapy również muszą być zwalniane.

    var current_code = ArrayList(u8).init(allocator);
    defer current_code.deinit();

    try generateCodesRecursive(root_node, &codes_map, allocator);
    return codes_map;
}

// 5. Zakoduj tekst
fn encodeText(
    text: []const u8,
    codes_map: *const HashMap(u8, []const u8, std.hash_map.AutoContext(u8), std.hash_map.default_max_load_percentage),
    allocator: Allocator,
) !ArrayList(u8) {
    var encoded_text = ArrayList(u8).init(allocator);
    // Nie robimy defer deinit, bo chcemy ją zwrócić

    for (text) |char| {
        if (codes_map.get(char)) |code| {
            try encoded_text.appendSlice(code);
        } else {
            // To nie powinno się zdarzyć, jeśli mapa kodów jest poprawna dla tekstu
            std.debug.print("Error: Character '{c}' not found in codes map.\n", .{char});
            return error.CharNotFoundInCodes;
        }
    }
    return encoded_text;
}

// 6. Zdekoduj tekst
fn decodeText(encoded_data: []const u8, root_node: *Node, allocator: Allocator) !ArrayList(u8) {
    var decoded_text = ArrayList(u8).init(allocator);
    // Nie robimy defer deinit, bo chcemy ją zwrócić

    var current_node = root_node;
    for (encoded_data) |bit| {
        if (bit == '0') {
            current_node = current_node.left orelse {
                std.debug.print("Decoding error: unexpected left traversal from null node.\n", .{});
                return error.DecodingError;
            };
        } else if (bit == '1') {
            current_node = current_node.right orelse {
                std.debug.print("Decoding error: unexpected right traversal from null node.\n", .{});
                return error.DecodingError;
            };
        } else {
            return error.InvalidBit;
        }

        if (current_node.isLeaf()) {
            if (current_node.char) |char_val| {
                try decoded_text.append(char_val);
                current_node = root_node; // Wróć do korzenia dla następnego znaku
            } else {
                // To nie powinno się zdarzyć dla poprawnie zbudowanego drzewa
                return error.DecodingErrorLeafHasNoChar;
            }
        }
    }
    return decoded_text;
}

// Funkcja do rekurencyjnego zwalniania węzłów drzewa
fn freeHuffmanTree(node: ?*Node, allocator: Allocator) void {
    if (node) |n| {
        freeHuffmanTree(n.left, allocator);
        freeHuffmanTree(n.right, allocator);
        allocator.destroy(n);
    }
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const text = "abracadabra";
    //const text = "beep boop beer!";
    //const text = "a";
    //const text = "";

    std.debug.print("Original text: {s}\n", .{text});

    if (text.len == 0) {
        std.debug.print("Input text is empty. Nothing to do.\n", .{});
        return;
    }

    // 1. Częstotliwości
    var freq_map = try calculateFrequencies(text, allocator);
    defer freq_map.deinit();

    std.debug.print("Frequencies:\n", .{});
    var it_freq = freq_map.iterator();
    while (it_freq.next()) |entry| {
        std.debug.print("  '{c}': {d}\n", .{ entry.key_ptr.*, entry.value_ptr.* });
    }

    // 2. & 3. Budowa drzewa
    const root_node = (try buildHuffmanTree(&freq_map, allocator)) orelse {
        std.debug.print("Failed to build Huffman tree (empty input or single char issue).\n", .{});
        return;
    };
    defer freeHuffmanTree(root_node, allocator);

    // 4. Generowanie kodów
    var codes_map = try generateCodes(root_node, allocator);
    defer {
        // Musimy zwolnić pamięć zaalokowaną dla każdego kodu w mapie
        var it_codes_deinit = codes_map.valueIterator();
        while (it_codes_deinit.next()) |code_slice_ptr| {
            allocator.free(code_slice_ptr.*);
        }
        codes_map.deinit();
    }

    std.debug.print("Huffman Codes:\n", .{});
    var it_codes = codes_map.iterator();
    while (it_codes.next()) |entry| {
        std.debug.print("  '{c}': {s}\n", .{ entry.key_ptr.*, entry.value_ptr.* });
    }

    // 5. Kodowanie
    var encoded_data_list = try encodeText(text, &codes_map, allocator);
    defer encoded_data_list.deinit();
    const encoded_data = encoded_data_list.items;

    std.debug.print("Encoded data: {s}\n", .{encoded_data});

    // 6. Dekodowanie
    var decoded_text_list = try decodeText(encoded_data, root_node.?, allocator);
    defer decoded_text_list.deinit();
    const decoded_text = decoded_text_list.items;

    std.debug.print("Decoded text: {s}\n", .{decoded_text});

    if (std.mem.eql(u8, text, decoded_text)) {
        std.debug.print("Success: Decoded text matches original text.\n", .{});
    } else {
        std.debug.print("Failure: Decoded text does not match original text.\n", .{});
    }
}
