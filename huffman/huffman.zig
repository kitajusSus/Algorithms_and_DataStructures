const std = @import("std");
const ArrayList = std.ArrayList;
const Allocator = std.mem.Allocator;
const Order = std.math.Order;
const stdout = std.io.getStdOut().writer();

// Węzeł drzewa Huffmana
const HuffmanNode = struct {
    character: ?u8, // Znak (null dla węzłów wewnętrznych)
    frequency: u32, // Częstotliwość wystąpienia znaku
    left: ?*HuffmanNode, // Lewy potomek
    right: ?*HuffmanNode, // Prawy potomek

    // Porównanie węzłów na podstawie częstotliwości
    pub fn compare(a: *HuffmanNode, b: *HuffmanNode) Order {
        if (a.frequency < b.frequency) {
            return .lt;
        } else if (a.frequency > b.frequency) {
            return .gt;
        } else {
            return .eq;
        }
    }
};

// Przechowuje kod Huffmana dla każdego znaku
const HuffmanCode = struct {
    code: ArrayList(bool),

    pub fn init(allocator: Allocator) HuffmanCode {
        return HuffmanCode{
            .code = ArrayList(bool).init(allocator),
        };
    }

    pub fn deinit(self: *HuffmanCode) void {
        self.code.deinit();
    }

    pub fn clone(self: HuffmanCode, allocator: Allocator) !HuffmanCode {
        var new_code = ArrayList(bool).init(allocator);
        try new_code.appendSlice(self.code.items);
        return HuffmanCode{ .code = new_code };
    }
};

// Tworzy drzewo Huffmana na podstawie tekstu
fn buildHuffmanTree(allocator: Allocator, text: []const u8) !?*HuffmanNode {
    // Liczy częstotliwość każdego znaku
    var freq = [_]u32{0} ** 256;
    for (text) |char| {
        freq[char] += 1;
    }

    // Tworzy kolejkę priorytetową węzłów dla znaków o niezerowej częstotliwości
    var priority_queue = ArrayList(*HuffmanNode).init(allocator);
    defer priority_queue.deinit();

    for (0..256) |i| {
        if (freq[i] > 0) {
            const node = try allocator.create(HuffmanNode);
            node.* = HuffmanNode{
                .character = @intCast(i),
                .frequency = freq[i],
                .left = null,
                .right = null,
            };
            try priority_queue.append(node);
        }
    }

    // Jeśli text zawiera tylko jeden rodzaj znaku, tworzymy dwa węzły
    if (priority_queue.items.len == 1) {
        const node = try allocator.create(HuffmanNode);
        node.* = HuffmanNode{
            .character = null,
            .frequency = priority_queue.items[0].frequency,
            .left = priority_queue.items[0],
            .right = null,
        };
        return node;
    }

    // Buduje drzewo Huffmana
    while (priority_queue.items.len > 1) {
        // Sortuje kolejkę priorytetową
        std.sort.insertion(*HuffmanNode, priority_queue.items, {}, struct {
            fn lessThan(_: void, a: *HuffmanNode, b: *HuffmanNode) bool {
                return a.compare(b) == .lt;
            }
        }.lessThan);

        // Pobiera dwa węzły o najniższej częstotliwości
        const left = priority_queue.orderedRemove(0);
        const right = priority_queue.orderedRemove(0);

        // Tworzy nowy węzeł wewnętrzny
        const internal_node = try allocator.create(HuffmanNode);
        internal_node.* = HuffmanNode{
            .character = null,
            .frequency = left.frequency + right.frequency,
            .left = left,
            .right = right,
        };

        try priority_queue.append(internal_node);
    }

    return if (priority_queue.items.len > 0) priority_queue.items[0] else null;
}

// Generuje kody Huffmana dla każdego znaku
fn generateHuffmanCodes(allocator: Allocator, root: *HuffmanNode, code: ArrayList(bool), huffman_codes: *[256]?HuffmanCode) !void {
    if (root.character) |char| {
        // Węzeł liściowy
        if (huffman_codes[@intCast(char)] == null) {
            huffman_codes[@intCast(char)] = HuffmanCode.init(allocator);
        }
        try huffman_codes[@intCast(char)].?.code.appendSlice(code.items);
    } else {
        // Węzeł wewnętrzny
        if (root.left) |left| {
            try code.append(false); // 0 dla lewego potomka
            try generateHuffmanCodes(allocator, left, code, huffman_codes);
            _ = code.pop();
        }

        if (root.right) |right| {
            try code.append(true); // 1 dla prawego potomka
            try generateHuffmanCodes(allocator, right, code, huffman_codes);
            _ = code.pop();
        }
    }
}

// Zapisuje skompresowany plik
fn writeCompressedFile(allocator: Allocator, input_text: []const u8, huffman_codes: [256]?HuffmanCode, output_filename: []const u8) !void {
    var outfile = try std.fs.cwd().createFile(output_filename, .{});
    defer outfile.close();
    var writer = outfile.writer();

    // Zapisuje tabelę kodów (format: [char][code_length][code_bits])
    try writer.writeByte(@as(u8, @intCast(countNonNullCodes(&huffman_codes))));
    for (0..256) |i| {
        if (huffman_codes[i]) |hcode| {
            try writer.writeByte(@as(u8, @intCast(i)));
            try writer.writeByte(@as(u8, @intCast(hcode.code.items.len)));
            
            // Zapisuje bity kodu w grupach po 8
            var bit_index: usize = 0;
            while (bit_index < hcode.code.items.len) {
                var byte: u8 = 0;
                var j: usize = 0;
                while (j < 8 and bit_index + j < hcode.code.items.len) : (j += 1) {
                    if (hcode.code.items[bit_index + j]) {
                        byte |= @as(u8, 1) << @intCast(7 - j);
                    }
                }
                try writer.writeByte(byte);
                bit_index += 8;
            }
        }
    }

    // Zapisuje zakodowany tekst
    var bit_buffer: u8 = 0;
    var bit_count: u3 = 0;

    for (input_text) |char| {
        const char_code = huffman_codes[char].?;
        for (char_code.code.items) |bit| {
            if (bit) {
                bit_buffer |= @as(u8, 1) << @intCast(7 - bit_count);
            }
            bit_count += 1;
            
            if (bit_count == 8) {
                try writer.writeByte(bit_buffer);
                bit_buffer = 0;
                bit_count = 0;
            }
        }
    }

    // Zapisuje ostatni bajt, jeśli jest niepełny
    if (bit_count > 0) {
        try writer.writeByte(bit_buffer);
    }
}

// Liczy liczbę niepustych kodów Huffmana
fn countNonNullCodes(huffman_codes: *const [256]?HuffmanCode) usize {
    var count: usize = 0;
    for (huffman_codes) |code| {
        if (code != null) {
            count += 1;
        }
    }
    return count;
}

// Zwalnia zasoby drzewa Huffmana
fn freeHuffmanTree(allocator: Allocator, node: ?*HuffmanNode) void {
    if (node) |n| {
        freeHuffmanTree(allocator, n.left);
        freeHuffmanTree(allocator, n.right);
        allocator.destroy(n);
    }
}

// Zwalnia zasoby kodów Huffmana
fn freeHuffmanCodes(huffman_codes: *[256]?HuffmanCode) void {
    for (0..256) |i| {
        if (huffman_codes[i]) |*code| {
            code.deinit();
            huffman_codes[i] = null;
        }
    }
}

// Główna funkcja kompresji
fn compressFile(allocator: Allocator, input_filename: []const u8, output_filename: []const u8) !void {
    try stdout.print("Kompresowanie pliku: {s} -> {s}\n", .{ input_filename, output_filename });

    // Wczytuje plik wejściowy
    const input_file = try std.fs.cwd().openFile(input_filename, .{});
    defer input_file.close();

    const file_size = try input_file.getEndPos();
    const input_text = try allocator.alloc(u8, file_size);
    defer allocator.free(input_text);

    const bytes_read = try input_file.readAll(input_text);
    if (bytes_read != file_size) {
        return error.ReadError;
    }

    // Buduje drzewo Huffmana
    const root = try buildHuffmanTree(allocator, input_text);
    defer if (root) |r| freeHuffmanTree(allocator, r);

    if (root == null) {
        try stdout.print("Pusty plik wejściowy.\n", .{});
        return;
    }

    // Generuje kody Huffmana
    var huffman_codes: [256]?HuffmanCode = [_]?HuffmanCode{null} ** 256;
    defer freeHuffmanCodes(&huffman_codes);

    var code = ArrayList(bool).init(allocator);
    defer code.deinit();

    try generateHuffmanCodes(allocator, root.?, code, &huffman_codes);

    // Zapisuje skompresowany plik
    try writeCompressedFile(allocator, input_text, huffman_codes, output_filename);

    try stdout.print("Kompresja zakończona pomyślnie.\n", .{});
}

// Funkcje dla dekompresji

// Odczytuje drzewo Huffmana z pliku
fn readHuffmanTree(allocator: Allocator, file: std.fs.File) !*HuffmanNode {
    var reader = file.reader();
    
    // Odczytuje liczbę znaków w tabeli
    const num_chars = try reader.readByte();
    
    // Tworzy mapę kodów Huffmana
    var huffman_codes: [256]?HuffmanCode = [_]?HuffmanCode{null} ** 256;
    defer freeHuffmanCodes(&huffman_codes);
    
    // Odczytuje kody dla każdego znaku
    var i: usize = 0;
    while (i < num_chars) : (i += 1) {
        const char = try reader.readByte();
        const code_length = try reader.readByte();
        
        huffman_codes[char] = HuffmanCode.init(allocator);
        
        // Odczytuje bity kodu
        var bits_to_read = code_length;
        while (bits_to_read > 0) {
            const byte = try reader.readByte();
            var j: u3 = 0;
            while (j < 8 and bits_to_read > 0) : (j += 1) {
                const bit = (byte & (@as(u8, 1) << @intCast(7 - j))) != 0;
                try huffman_codes[char].?.code.append(bit);
                bits_to_read -= 1;
            }
        }
    }
    
    // Rekonstruuje drzewo Huffmana z kodów
    var root = try allocator.create(HuffmanNode);
    root.* = HuffmanNode{
        .character = null,
        .frequency = 0,
        .left = null,
        .right = null,
    };
    
    for (0..256) |c| {
        if (huffman_codes[c]) |hcode| {
            var current = root;
            
            for (hcode.code.items) |bit| {
                if (bit) {
                    // Prawy potomek (1)
                    if (current.right == null) {
                        const new_node = try allocator.create(HuffmanNode);
                        new_node.* = HuffmanNode{
                            .character = null,
                            .frequency = 0,
                            .left = null,
                            .right = null,
                        };
                        current.right = new_node;
                    }
                    current = current.right.?;
                } else {
                    // Lewy potomek (0)
                    if (current.left == null) {
                        const new_node = try allocator.create(HuffmanNode);
                        new_node.* = HuffmanNode{
                            .character = null,
                            .frequency = 0,
                            .left = null,
                            .right = null,
                        };
                        current.left = new_node;
                    }
                    current = current.left.?;
                }
            }
            
            current.character = @intCast(c);
        }
    }
    
    return root;
}

// Dekompresuje plik
fn decompressFile(allocator: Allocator, input_filename: []const u8, output_filename: []const u8) !void {
    try stdout.print("Dekompresowanie pliku: {s} -> {s}\n", .{ input_filename, output_filename });

    // Otwiera plik wejściowy
    const input_file = try std.fs.cwd().openFile(input_filename, .{});
    defer input_file.close();

    // Odczytuje drzewo Huffmana
    const root = try readHuffmanTree(allocator, input_file);
    defer freeHuffmanTree(allocator, root);

    // Tworzy plik wyjściowy
    var output_file = try std.fs.cwd().createFile(output_filename, .{});
    defer output_file.close();
    var writer = output_file.writer();

    // Dekoduje dane
    var reader = input_file.reader();
    var current = root;
    var byte: u8 = 0;
    var bit_position: u3 = 0;

    while (true) {
        // Odczytuje nowy bajt kiedy potrzebny
        if (bit_position == 0) {
            byte = reader.readByte() catch |err| {
                if (err == error.EndOfStream) {
                    break;
                }
                return err;
            };
        }

        // Pobiera bit i przesuwa się w drzewie
        const bit = (byte & (@as(u8, 1) << @intCast(7 - bit_position))) != 0;

        if (bit) {
            current = current.right orelse root;
        } else {
            current = current.left orelse root;
        }

        // Jeśli dotarliśmy do liścia, zapisujemy znak
        if (current.character) |char| {
            try writer.writeByte(char);
            current = root;
        }

        // Przesuwamy się do następnego bitu
        bit_position = @intCast((@as(u4, bit_position) + 1) % 8);
    }

    try stdout.print("Dekompresja zakończona pomyślnie.\n", .{});
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    var args = std.process.args();
    _ = args.skip(); // Skips the program name

    // Sprawdza argumenty
    const operation = args.next(allocator) orelse {
        try stdout.print("Użycie: program [compress|decompress] plik_wejściowy plik_wyjściowy\n", .{});
        return;
    };
    defer allocator.free(operation);

    const input_file = args.next(allocator) orelse {
        try stdout.print("Brak pliku wejściowego.\n", .{});
        return;
    };
    defer allocator.free(input_file);

    const output_file = args.next(allocator) orelse {
        try stdout.print("Brak pliku wyjściowego.\n", .{});
        return;
    };
    defer allocator.free(output_file);

    if (std.mem.eql(u8, operation, "compress")) {
        try compressFile(allocator, input_file, output_file);
    } else if (std.mem.eql(u8, operation, "decompress")) {
        try decompressFile(allocator, input_file, output_file);
    } else {
        try stdout.print("Nieznana operacja: {s}. Użyj 'compress' lub 'decompress'.\n", .{operation});
    }
}
