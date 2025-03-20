const std = @import("std");

// Person struct (equivalent to Person class in C++)
const Person = struct {
    lastName: []const u8,
    firstName: []const u8,
    age: i32,

    // Constructor
    pub fn init(last: []const u8, first: []const u8, a: i32) Person {
        return Person{
            .lastName = last,
            .firstName = first,
            .age = a,
        };
    }

    // Display method
    pub fn displayPerson(self: Person) void {
        std.debug.print(" //Last Name: {s}", .{self.lastName});
        std.debug.print(" //First Name: {s}", .{self.firstName});
        std.debug.print(" //Age: {}\n", .{self.age});
    }

    // Getter method
    pub fn getLast(self: Person) []const u8 {
        return self.lastName;
    }
};

// ArrayInOb struct
const ArrayInOb = struct {
    // In Zig we'll use an ArrayList instead of a vector
    persons: std.ArrayList(*Person),
    nElems: usize,
    allocator: std.mem.Allocator,

    // Constructor
    pub fn init(allocator: std.mem.Allocator, max: usize) !ArrayInOb {
        var persons = std.ArrayList(*Person).init(allocator);
        try persons.resize(max);

        return ArrayInOb{
            .persons = persons,
            .nElems = 0,
            .allocator = allocator,
        };
    }

    // Deinitializer (similar to destructor in C++)
    pub fn deinit(self: *ArrayInOb) void {
        // Free all Person instances
        for (0..self.nElems) |i| {
            self.allocator.destroy(self.persons.items[i]);
        }
        // Free the ArrayList
        self.persons.deinit();
    }

    // Insert a person into the array
    pub fn insert(self: *ArrayInOb, last: []const u8, first: []const u8, age: i32) !void {
        const person = try self.allocator.create(Person);
        person.* = Person.init(last, first, age);
        self.persons.items[self.nElems] = person;
        self.nElems += 1;
    }

    // Display all persons in the array
    pub fn display(self: ArrayInOb) void {
        for (0..self.nElems) |j| {
            std.debug.print("{*}", .{self.persons.items[j]});
            self.persons.items[j].displayPerson();
        }
    }

    // Insertion sort implementation
    pub fn insertionSort(self: *ArrayInOb) void {
        var out: usize = 1;
        while (out < self.nElems) : (out += 1) {
            const temp = self.persons.items[out];
            var in: usize = out;

            // Zig doesn't have string comparison built-in, so we'll use std.mem.lessThan
            while (in > 0) {
                // Compare last names
                const current = self.persons.items[in - 1].getLast();
                const comparison = std.mem.lessThan(u8, temp.getLast(), current);

                if (!comparison) break;

                self.persons.items[in] = self.persons.items[in - 1];
                in -= 1;
            }
            self.persons.items[in] = temp;
        }
    }
};

pub fn main() !void {
    // Get a standard allocator
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = gpa.allocator();
    defer _ = gpa.deinit();
    const maxSize = 100;
    var arr = try ArrayInOb.init(allocator, maxSize);
    defer arr.deinit();
    try arr.insert("Jasny", "Gwint", 14);
    try arr.insert("Dave", "Bajo", 15);
    try arr.insert("Fajny", "Gwint", 2);
    try arr.insert("Szary", "Gwint", 24);
    try arr.insert("Niebieski", "Gwint", 134);
    try arr.insert("Ciemny", "Gwint", 44);
    std.debug.print("Before sorting:\n", .{});
    arr.display();
    arr.insertionSort();
    std.debug.print("\nAfter sorting:\n", .{});
    arr.display();
}
