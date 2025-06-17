const std = @import("std");

const Allocator = std.mem.Allocator;

const Node = struct {
    id: usize,
    neighbors: std.ArrayList(usize),
};

const Graph = struct {
    allocator: *Allocator,
    nodes: std.ArrayList(Node),

    pub fn init(allocator: *Allocator) !Graph {
        return Graph{
            .allocator = allocator,
            .nodes = try std.ArrayList(Node).init(allocator),
        };
    }

    pub fn deinit(self: *Graph) void {
        for (self.nodes.items) |*node| {
            node.neighbors.deinit();
        }
        self.nodes.deinit();
    }

    pub fn addNode(self: *Graph) !usize {
        const id = self.nodes.items.len;
        const neighbors = try std.ArrayList(usize).init(self.allocator);
        try self.nodes.append(Node{ .id = id, .neighbors = neighbors });
        return id;
    }

    pub fn addEdge(self: *Graph, a: usize, b: usize) !void {
        try self.nodes.items[a].neighbors.append(b);
        try self.nodes.items[b].neighbors.append(a); // dla grafu nieskierowanego
    }

    pub fn print(self: *Graph) void {
        for (self.nodes.items) |node| {
            std.debug.print("Node {d}: ", .{node.id});
            for (node.neighbors.items) |neighbor| {
                std.debug.print("{d} ", .{neighbor});
            }
            std.debug.print("\n", .{});
        }
    }
};

pub fn main() !void {
    var allocator = std.heap.page_allocator;
    var graph = try Graph.init(&allocator); // przekazanie wskaźnika

    defer graph.deinit();

    const a = try graph.addNode();
    const b = try graph.addNode();
    const c = try graph.addNode();

    try graph.addEdge(a, b);
    try graph.addEdge(b, c);
    try graph.addEdge(c, a);

    graph.print();
}
