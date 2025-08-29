#include <vector>
#include <queue>
#include <cassert>

std::vector<int> bfs(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> order;
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int u : graph[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
    return order;
}

void dfsRec(const std::vector<std::vector<int>>& graph, int v,
            std::vector<bool>& visited, std::vector<int>& order) {
    visited[v] = true;
    order.push_back(v);
    for (int u : graph[v]) {
        if (!visited[u])
            dfsRec(graph, u, visited, order);
    }
}

std::vector<int> dfs(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> order;
    std::vector<bool> visited(graph.size(), false);
    dfsRec(graph, start, visited, order);
    return order;
}

int main() {
    std::vector<std::vector<int>> g = {
        {1, 2}, // 0
        {0, 3}, // 1
        {0, 3}, // 2
        {1, 2}  // 3
    };
    auto bfsOrder = bfs(g, 0);
    auto dfsOrder = dfs(g, 0);
    std::vector<int> expectedBfs = {0, 1, 2, 3};
    std::vector<int> expectedDfs = {0, 1, 3, 2};
    assert(bfsOrder == expectedBfs);
    assert(dfsOrder == expectedDfs);
    return 0;
}
