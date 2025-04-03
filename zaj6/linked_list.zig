const std = @import("std");

// Struktura Link (węzeł)
const Link = struct {
    iData: i32,
    dData: f64,
    pNext: ?*Link,

    // Konstruktor
    pub fn init(id: i32, dd: f64) !*Link {
        const self = try std.heap.page_allocator.create(Link);
        self.* = .{
            .iData = id,
            .dData = dd,
            .pNext = null,
        };
        return self;
    }

    // Wyświetlanie elementu
    pub fn displayLink(self: *Link) void {
        std.debug.print("{{{}, {d:.2}}}", .{ self.iData, self.dData });
    }
};

// Lista połączona
const LinkedList = struct {
    pFirst: ?*Link,

    // Konstruktor
    pub fn init() LinkedList {
        return LinkedList{
            .pFirst = null,
        };
    }

    // Sprawdzanie czy lista jest pusta
    pub fn isEmpty(self: *LinkedList) bool {
        return self.pFirst == null;
    }

    // Wstawianie na początek
    pub fn insertFirst(self: *LinkedList, id: i32, dd: f64) !void {
        var pNewLink = try Link.init(id, dd);
        pNewLink.pNext = self.pFirst;
        self.pFirst = pNewLink;
    }

    // Usuwanie pierwszego elementu
    pub fn removeFirst(self: *LinkedList) void {
        if (self.pFirst) |first| {
            self.pFirst = first.pNext;
            std.heap.page_allocator.destroy(first);
        }
    }

    // Wyświetlanie listy
    pub fn displayList(self: *LinkedList) void {
        std.debug.print("Lista (pierwsza -> ostatnia): ", .{});
        var current = self.pFirst;
        while (current) |curr| {
            curr.displayLink();
            current = curr.pNext;
        }
        std.debug.print("\n", .{});
    }

    // Zwalnianie pamięci
    pub fn deinit(self: *LinkedList) void {
        while (self.pFirst) |first| {
            self.pFirst = first.pNext;
            std.heap.page_allocator.destroy(first);
        }
    }
};

pub fn main() !void {
    // Utworzenie nowej pustej listy
    var lista = LinkedList.init();
    defer lista.deinit(); // Automatyczne zwalnianie pamięci przy wyjściu z funkcji

    // Sprawdzenie czy lista jest pusta
    std.debug.print("Czy lista jest pusta? {s}\n", .{if (lista.isEmpty()) "Tak" else "Nie"});

    // Dodawanie elementów na początek listy
    std.debug.print("\nDodawanie elementów do listy:\n", .{});
    try lista.insertFirst(22, 2.99);
    try lista.insertFirst(44, 4.99);
    try lista.insertFirst(66, 6.99);
    try lista.insertFirst(88, 8.99);

    // Wyświetlenie listy po dodaniu elementów
    lista.displayList();

    // Sprawdzenie czy lista jest pusta po dodaniu elementów
    std.debug.print("\nCzy lista jest pusta? {s}\n", .{if (lista.isEmpty()) "Tak" else "Nie"});

    // Usuwanie pierwszego elementu
    std.debug.print("\nUsuwanie pierwszego elementu...\n", .{});
    lista.removeFirst();
    lista.displayList();

    // Dodanie nowego elementu na początek
    std.debug.print("\nDodanie nowego elementu na początek...\n", .{});
    try lista.insertFirst(99, 9.99);
    lista.displayList();

    // Demonstracja usuwania wszystkich elementów
    std.debug.print("\nUsuwanie wszystkich elementów z listy:\n", .{});
    while (!lista.isEmpty()) {
        lista.removeFirst();
        lista.displayList();
    }

    // Sprawdzenie końcowego stanu listy
    std.debug.print("\nCzy lista jest pusta? {s}\n", .{if (lista.isEmpty()) "Tak" else "Nie"});
}
