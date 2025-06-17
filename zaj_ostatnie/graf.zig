const std = @import("std");

const Allocator = std.mem.Allocator;

const Node = struct {
    id: usize,
    neighbors: std.ArrayListUnmanaged(usize),

    pub fn init(id: usize) Node {
        return Node{
            .id = id,
            .neighbors = .{},
        };
    }

    pub fn deinit(self: *Node, allocator: Allocator) void {
        self.neighbors.deinit(allocator);
    }
};

const Graph = struct {
    allocator: Allocator,
    nodes: std.ArrayListUnmanaged(Node),

    pub fn init(allocator: Allocator) Graph {
        return Graph{
            .allocator = allocator,
            .nodes = .{},
        };
    }

    pub fn deinit(self: *Graph) void {
        for (self.nodes.items) |*node| {
            node.deinit(self.allocator);
        }
        self.nodes.deinit(self.allocator);
    }

    pub fn addNode(self: *Graph) !usize {
        const id = self.nodes.items.len;
        const node = Node.init(id);
        try self.nodes.append(self.allocator, node);
        return id;
    }

    pub fn addEdge(self: *Graph, a: usize, b: usize) !void {
        try self.nodes.items[a].neighbors.append(self.allocator, b);
        try self.nodes.items[b].neighbors.append(self.allocator, a); // dla grafu nieskierowanego
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
    var graph = Graph.init(std.heap.page_allocator);
    defer graph.deinit();

    const a = try graph.addNode();
    const b = try graph.addNode();
    const c = try graph.addNode();

    try graph.addEdge(a, b);
    try graph.addEdge(b, c);
    try graph.addEdge(c, a);

    graph.print();
}
