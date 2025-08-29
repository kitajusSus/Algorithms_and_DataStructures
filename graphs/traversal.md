# Graph Traversal

This document describes Breadth-First Search (BFS) and Depth-First Search (DFS) on a graph represented as an adjacency list.

## Sample Graph

Consider the following undirected graph:

```
0 -- 1 -- 2
|    |    |
3 -- 4 -- 5
```

The adjacency list for this graph is:

```
0: [1, 3]
1: [0, 2, 4]
2: [1, 5]
3: [0, 4]
4: [1, 3, 5]
5: [2, 4]
```

## BFS

BFS explores the graph level by level using a **queue**. Starting from vertex 0, the traversal order is `0, 1, 3, 2, 4, 5`.

## DFS

DFS explores as deep as possible using a **stack**. Starting from vertex 0, a possible traversal order is `0, 1, 2, 5, 4, 3`.
