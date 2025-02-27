
const std = @import("std");

/// Struktura węzła drzewa Huffmana.
const HuffmanNode = struct {
    frequency: usize,   // liczba wystąpień (lub suma w węźle wewn.)
    symbol: u8,         // bajt (znak) - tylko w liściach ma znaczenie
    leftChild: ?*HuffmanNode,
    rightChild: ?*HuffmanNode,
};

/// Struktura pomocnicza: częstotliwości + zakodowane bity.
const FreqAndEncoded = struct {
    freq: [256]usize,
    encodedBits: []const u8,
};

/// 1. Czytanie pliku w całości do bufora.
fn readEntireFile(allocator: *std.mem.Allocator, path: []const u8) ![]u8 {
    var file = try std.fs.cwd().openFile(path, .{ .read = true });
    defer file.close();

    const info = try file.stat();
    const size = info.size;

    var buffer = try allocator.alloc(u8, size);
    const readBytes = try file.readAll(buffer);
    if (readBytes != size) {
        return error.UnexpectedEof;
    }
    return buffer;
}

/// 2. Zapis całego bufora do pliku (np. używane przy dekodowaniu).
fn writeEntireFile(path: []const u8, data: []const u8) !void {
    var file = try std.fs.cwd().createFile(path, .{ .write = true, .truncate = true });
    defer file.close();

    try file.writer().writeAll(data);
}

/// 3. Zliczenie częstotliwości (ile razy występuje każdy bajt 0..255).
fn countFrequencies(data: []const u8) [256]usize {
    var freq: [256]usize = [_]usize{0} ** 256;
    for (data) |b| {
        freq[b] += 1;
    }
    return freq;
}

/// 4. Budowa drzewa Huffmana na podstawie częstotliwości.
///    Kluczowe: przechowujemy wskaźniki do alokowanych węzłów.
fn buildHuffmanTree(
    allocator: *std.mem.Allocator,
    freq: [256]usize
) !*HuffmanNode {
    // Zbierz wskaźniki do węzłów (tylko tam, gdzie freq > 0)
    var nodePtrs = try allocator.alloc(*HuffmanNode, 0);
    defer allocator.free(nodePtrs);

    var countNonZero: usize = 0;

    for (freq, idx) |f, i| {
        if (f > 0) {
            countNonZero += 1;
            nodePtrs = try std.mem.resize(allocator, nodePtrs, *HuffmanNode, countNonZero);

            // Alokujemy nowy węzeł
            let newNodePtr = try allocator.create(HuffmanNode);
            newNodePtr.* = HuffmanNode{
                .frequency = f,
                .symbol = @as(u8, i),
                .leftChild = null,
                .rightChild = null,
            };
            nodePtrs[countNonZero - 1] = newNodePtr;
        }
    }

    // Jeśli tylko 1 rodzaj bajtu, sztucznie dublujemy, by mieć 2 liście
    if (countNonZero == 1) {
        countNonZero += 1;
        nodePtrs = try std.mem.resize(allocator, nodePtrs, *HuffmanNode, countNonZero);

        // duplikujemy istniejący węzeł
        let clonedNodePtr = try allocator.create(HuffmanNode);
        clonedNodePtr.* = nodePtrs[countNonZero - 2].*;
        nodePtrs[countNonZero - 1] = clonedNodePtr;
    } else if (countNonZero == 0) {
        // brak danych
        return null;
    }

    var n = countNonZero;
    while (n > 1) {
        // Sortowanie tablicy wskaźników do węzłów po częstotliwości
        try sortNodePointers(nodePtrs[0..n]);

        const nodeA = nodePtrs[0];
        const nodeB = nodePtrs[1];

        // Tworzymy węzeł-rodzic
        const parentPtr = try allocator.create(HuffmanNode);
        parentPtr.* = HuffmanNode{
            .frequency = nodeA.frequency + nodeB.frequency,
            .symbol = 0, // w węzłach wewn. nieważne
            .leftChild = nodeA,
            .rightChild = nodeB,
        };

        // Zastępujemy dwa węzły nowym węzłem (skracamy tablicę o 1)
        nodePtrs[0] = parentPtr;
        nodePtrs[1] = nodePtrs[n - 1];
        n -= 1;
    }

    return nodePtrs[0]; // wskaźnik do korzenia
}

/// Sortowanie tablicy *wskaźników* rosnąco po `frequency`.
fn sortNodePointers(slice: []*HuffmanNode) !void {
    const sort = std.sort.sort;
    sort(*HuffmanNode, slice, struct {
        fn compare(a: *HuffmanNode, b: *HuffmanNode) std.math.order {
            if (a.frequency < b.frequency) return .less;
            if (a.frequency > b.frequency) return .greater;
            return .equal;
        }
    }) catch return;
}

/// 5. Rekurencyjne generowanie kodów (mapa: bajt -> ciąg '0'/'1').
fn buildCodesImpl(
    allocator: *std.mem.Allocator,
    node: *HuffmanNode,
    prefix: []const u8,
    codes: *std.HashMapUnmanaged(u8, []u8),
) !void {
    if (node.leftChild == null and node.rightChild == null) {
        // liść
        try codes.put(node.symbol, prefix);
        return;
    }
    // Lewo => '0'
    if (node.leftChild != null) {
        const leftPath = try appendBit(allocator, prefix, '0');
        defer allocator.free(leftPath);
        try buildCodesImpl(allocator, node.leftChild.?, leftPath, codes);
    }
    // Prawo => '1'
    if (node.rightChild != null) {
        const rightPath = try appendBit(allocator, prefix, '1');
        defer allocator.free(rightPath);
        try buildCodesImpl(allocator, node.rightChild.?, rightPath, codes);
    }
}

/// Dokleja jeden znak ('0' lub '1') do końca istniejącego ciągu.
fn appendBit(
    allocator: *std.mem.Allocator,
    prefix: []const u8,
    bit: u8
) ![]u8 {
    var newPath = try allocator.alloc(u8, prefix.len + 1);
    std.mem.copy(u8, newPath, prefix);
    newPath[prefix.len] = bit;
    return newPath;
}

/// Funkcja główna do stworzenia kompletnej mapy kodów.
fn buildCodes(
    allocator: *std.mem.Allocator,
    root: ?*HuffmanNode
) !std.HashMapUnmanaged(u8, []u8) {
    var codes = std.HashMapUnmanaged(u8, []u8).init(allocator);

    if (root == null) {
        // brak danych, brak kodów
        return codes;
    }
    try buildCodesImpl(allocator, root.?, &[_]u8{}, &codes);
    return codes;
}

/// 6. Kodowanie pliku (bufora) - zwraca ciąg bitów w postaci ASCII '0'/'1'.
fn encodeBuffer(
    allocator: *std.mem.Allocator,
    data: []const u8,
    codes: std.HashMapUnmanaged(u8, []u8)
) ![]u8 {
    var totalBits: usize = 0;

    // Obliczamy łączną liczbę bitów
    for (data) |b| {
        const code = codes.get(b) orelse return error.Invalid;
        totalBits += code.len;
    }

    var encoded = try allocator.alloc(u8, totalBits);
    var pos: usize = 0;
    for (data) |b| {
        const code = codes.get(b) orelse return error.Invalid;
        for (code) |bit| {
            encoded[pos] = bit;
            pos += 1;
        }
    }
    return encoded;
}

/// 7. Odczyt częstotliwości z pliku (pierwsze 256 * 8 bajtów) i pozostałych bitów.
fn readFrequenciesFromFile(
    allocator: *std.mem.Allocator,
    compressed: []const u8
) !FreqAndEncoded {
    if (compressed.len < 256 * 8) {
        return error.Invalid;
    }

    var freq: [256]usize = [_]usize{0} ** 256;

    var offset: usize = 0;
    for (freq) |*f| {
        if (offset + 8 > compressed.len) return error.Invalid;

        const val = @intFromBytes(u64, compressed[offset..offset+8], .little);
        offset += 8;
        f.* = @intCast(usize, val);
    }

    // Reszta to zakodowany ciąg bitów ('0'/'1'):
    const encodedBits = compressed[offset..];

    return .{
        .freq = freq,
        .encodedBits = encodedBits,
    };
}

/// 8. Dekodowanie zakodowanego ciągu bitów '0'/'1' za pomocą drzewa Huffmana.
fn decodeBuffer(
    allocator: *std.mem.Allocator,
    encodedBits: []const u8,
    root: ?*HuffmanNode
) ![]u8 {
    if (root == null) {
        // brak drzewa => brak danych
        return allocator.alloc(u8, 0);
    }

    var result = try allocator.alloc(u8, 0);
    var currentNode = root.?;

    for (encodedBits) |bit| {
        if (bit == '0') {
            currentNode = currentNode.leftChild.?;
        } else if (bit == '1') {
            currentNode = currentNode.rightChild.?;
        } else {
            return error.Invalid; // nieprawidłowy znak w strumieniu
        }

        // Jeżeli dotarliśmy do liścia
        if (currentNode.leftChild == null and currentNode.rightChild == null) {
            const newLen = result.len + 1; // <-- Poprawione
            result = try std.mem.resize(allocator, result, u8, newLen);
            result[newLen - 1] = currentNode.symbol;
            // wracamy do korzenia
            currentNode = root.?;
        }
    }

    return result;
}

/// 9. Zwalnianie drzewa Huffmana (rekurencyjnie).
fn destroyTree(allocator: *std.mem.Allocator, node: ?*HuffmanNode) void {
    if (node == null) return;
    const realNode = node.?;

    if (realNode.leftChild) |lc| {
        destroyTree(allocator, lc);
    }
    if (realNode.rightChild) |rc| {
        destroyTree(allocator, rc);
    }
    allocator.destroy(realNode);
}

/// Program główny.
/// Przykład użycia:
///   zig run huffman.zig encode input.txt output.huff
///   zig run huffman.zig decode input.huff output.txt
pub fn main() !void {
    const allocator = std.heap.page_allocator;

    var args = std.process.argsAlloc(allocator) catch {
        std.debug.print("Błąd podczas pobierania argumentów!\n", .{});
        return;
    };
    defer std.process.argsFree(allocator, args);

    if (args.len < 4) {
        std.debug.print("Użycie:\n", .{});
        std.debug.print("  {s} encode <plik_wejsciowy> <plik_wyjsciowy>\n", .{ args[0] });
        std.debug.print("  {s} decode <plik_wejsciowy> <plik_wyjsciowy>\n", .{ args[0] });
        return;
    }

    const command = args[1];
    const inputPath = args[2];
    const outputPath = args[3];

    if (std.mem.eql(u8, command, "encode")) {
        // ========================================
        //              KODOWANIE
        // ========================================
        // 1) Wczytaj dane wejściowe
        var inputData = try readEntireFile(allocator, inputPath);
        defer allocator.free(inputData);

        if (inputData.len == 0) {
            // plik pusty? Zapisz 256 zer w freq + brak bitów
            var freqEmpty: [256]usize = [_]usize{0} ** 256;
            const headerSize = 256 * 8;
            var outputBuffer = try allocator.alloc(u8, headerSize);
            defer allocator.free(outputBuffer);
            std.mem.set(u8, outputBuffer, 0);

            try writeEntireFile(outputPath, outputBuffer);
            std.debug.print("Pusty plik skompresowany do pustych freq.\n", .{});
            return;
        }

        // 2) Zlicz częstotliwości
        const freq = countFrequencies(inputData);

        // 3) Budujemy drzewo Huffmana
        const root = try buildHuffmanTree(allocator, freq);
        defer destroyTree(allocator, root);

        // 4) Generujemy kody
        var codes = try buildCodes(allocator, root);
        defer {
            // Zwolnij pamięć tablic w mapie
            for (codes.iterator()) |entry| {
                allocator.free(entry.value);
            }
            codes.deinit();
        }

        // 5) Kodujemy dane -> ciąg bitów '0'/'1'
        const encodedBits = try encodeBuffer(allocator, inputData, codes);
        defer allocator.free(encodedBits);

        // 6) Przygotuj bufor: 256 freq (8 bajtów na freq) + bity
        const headerSize = 256 * 8;
        const outputSize = headerSize + encodedBits.len;
        var outputBuffer = try allocator.alloc(u8, outputSize);
        defer allocator.free(outputBuffer);

        var offset: usize = 0;
        for (freq) |f| {
            let val = @intCast(u64, f);
            const leBytes = @intToBytes(u64, val, .little);
            std.mem.copy(u8, outputBuffer[offset..offset+8], leBytes);
            offset += 8;
        }
        // Zapis ciągu bitów
        std.mem.copy(u8, outputBuffer[offset..offset+encodedBits.len], encodedBits);

        try writeEntireFile(outputPath, outputBuffer);
        std.debug.print("Zakodowano plik '{s}' do '{s}' (Huffman)\n", .{ inputPath, outputPath });

    } else if (std.mem.eql(u8, command, "decode")) {
        // ========================================
        //              DEKODOWANIE
        // ========================================
        // 1) Wczytujemy plik (freq + bity)
        var compressedData = try readEntireFile(allocator, inputPath);
        defer allocator.free(compressedData);

        if (compressedData.len < 256 * 8) {
            // plik za mały, będzie pusty
            var emptySlice = try allocator.alloc(u8, 0);
            defer allocator.free(emptySlice);
            try writeEntireFile(outputPath, emptySlice);
            std.debug.print("Brak danych (lub za mały plik Huffmana), zapisano pusty wynik.\n", .{});
            return;
        }

        // 2) Odczytujemy freq i bity
        const result = try readFrequenciesFromFile(allocator, compressedData);
        const freq = result.freq;
        const encodedBits = result.encodedBits;

        // Czy w ogóle coś było zliczone?
        var sumFreq: usize = 0;
        for (freq) |f| sumFreq += f;
        if (sumFreq == 0) {
            // nic nie ma => plik był pusty
            var emptySlice = try allocator.alloc(u8, 0);
            defer allocator.free(emptySlice);
            try writeEntireFile(outputPath, emptySlice);
            std.debug.print("Dekodowano pusty plik Huffmana.\n", .{});
            return;
        }

        // 3) Odbudowujemy drzewo
        const root = try buildHuffmanTree(allocator, freq);
        defer destroyTree(allocator, root);

        // 4) Dekodujemy bity
        const decodedData = try decodeBuffer(allocator, encodedBits, root);
        defer allocator.free(decodedData);

        // 5) Zapisujemy wynik
        try writeEntireFile(outputPath, decodedData);
        std.debug.print("Zdekodowano plik '{s}' do '{s}'\n", .{ inputPath, outputPath });

    } else {
        std.debug.print("Nieznane polecenie: {s}\n", .{ command });
        return;
    }
}

