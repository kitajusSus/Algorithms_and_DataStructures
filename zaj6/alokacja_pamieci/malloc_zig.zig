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

//W Zig, w pętli `for` nad tablicą, możesz iterować na dwa sposoby:

//1. **Jednym elementem**: Jeśli używasz tylko jednej zmiennej, np. `|item|`, to iterujesz po wartościach elementów tablicy.
//2. **Dwoma elementami**: Jeśli używasz dwóch zmiennych, np. `|*item, index|`, to:
 //  - `*item` to wskaźnik do elementu tablicy (możesz modyfikować wartość).
//   - `index` to indeks aktualnego elementu w tablicy.

//W kodzie:
//- Pierwsza pętla `for (arr) |*item, index|` używa wskaźnika `*item` do modyfikacji wartości w tablicy oraz `index` do przypisania wartości zależnej od indeksu.
//- Druga pętla `for (arr) |item|` iteruje tylko po wartościach elementów tablicy, aby je wypisać.

//To pozwala na różne operacje w zależności od potrzeb: modyfikację w pierwszej pętli i odczyt w drugiej.


