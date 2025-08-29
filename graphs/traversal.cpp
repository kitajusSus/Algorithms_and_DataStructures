#include <bits/stdc++.h>
using namespace std;

// Perform Breadth-First Search (BFS) on an adjacency list.
// BFS uses a queue to explore vertices level by level.
vector<int> bfs(int start, const vector<vector<int>>& adj) {
    vector<int> order;
    vector<bool> visited(adj.size(), false);
    queue<int> q; // queue for BFS

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);

        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }

    return order;
}

// Perform Depth-First Search (DFS) on an adjacency list.
// DFS uses a stack to explore as deep as possible.
vector<int> dfs(int start, const vector<vector<int>>& adj) {
    vector<int> order;
    vector<bool> visited(adj.size(), false);
    stack<int> st; // stack for DFS

    st.push(start);

    while (!st.empty()) {
        int v = st.top();
        st.pop();

        if (visited[v]) continue;
        visited[v] = true;
        order.push_back(v);

        // push neighbors in reverse to mimic recursive order
        for (auto it = adj[v].rbegin(); it != adj[v].rend(); ++it) {
            if (!visited[*it]) {
                st.push(*it);
            }
        }
    }

    return order;
}

int main() {
    // Example usage with a simple undirected graph
    // 0 -- 1 -- 2
    // |    |    |
    // 3 -- 4 -- 5
    vector<vector<int>> adj = {
        {1,3},     // 0
        {0,2,4},   // 1
        {1,5},     // 2
        {0,4},     // 3
        {1,3,5},   // 4
        {2,4}      // 5
    };

    auto bfs_order = bfs(0, adj);
    auto dfs_order = dfs(0, adj);

    cout << "BFS order: ";
    for (int v : bfs_order) cout << v << ' ';
    cout << '\n';

    cout << "DFS order: ";
    for (int v : dfs_order) cout << v << ' ';
    cout << '\n';

    return 0;
}
