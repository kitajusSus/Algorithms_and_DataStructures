#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <algorithm>

struct Graph {
    struct Edge {
        int to;
        double weight;
    };
    std::vector<std::vector<Edge>> adj;
    std::vector<std::pair<double, double>> coords;

    static Graph loadFromFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        int n, m;
        file >> n >> m;
        Graph g;
        g.adj.assign(n, {});
        g.coords.resize(n);
        for (int i = 0; i < n; ++i) {
            double x, y;
            file >> x >> y;
            g.coords[i] = {x, y};
        }
        for (int i = 0; i < m; ++i) {
            int u, v;
            double w;
            file >> u >> v >> w;
            g.adj[u].push_back({v, w});
            g.adj[v].push_back({u, w});
        }
        return g;
    }
};

double heuristic(const Graph &g, int u, int goal) {
    auto [x1, y1] = g.coords[u];
    auto [x2, y2] = g.coords[goal];
    double dx = x1 - x2, dy = y1 - y2;
    return std::sqrt(dx * dx + dy * dy);
}

std::vector<int> astar(const Graph &g, int start, int goal) {
    const double INF = std::numeric_limits<double>::infinity();
    std::vector<double> gScore(g.adj.size(), INF), fScore(g.adj.size(), INF);
    std::vector<int> parent(g.adj.size(), -1);
    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> open;

    gScore[start] = 0.0;
    fScore[start] = heuristic(g, start, goal);
    open.push({fScore[start], start});

    while (!open.empty()) {
        auto [f, u] = open.top();
        open.pop();
        if (u == goal) break;
        for (const auto &e : g.adj[u]) {
            double tentative = gScore[u] + e.weight;
            if (tentative < gScore[e.to]) {
                gScore[e.to] = tentative;
                fScore[e.to] = tentative + heuristic(g, e.to, goal);
                parent[e.to] = u;
                open.push({fScore[e.to], e.to});
            }
        }
    }

    std::vector<int> path;
    if (parent[goal] == -1 && start != goal) {
        return path; // empty path when unreachable
    }
    for (int v = goal; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

int main(int argc, char **argv) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " graph.txt start goal" << std::endl;
        return 1;
    }
    Graph g = Graph::loadFromFile(argv[1]);
    int start = std::stoi(argv[2]);
    int goal = std::stoi(argv[3]);
    auto path = astar(g, start, goal);
    if (path.empty()) {
        std::cout << "No path" << std::endl;
        return 0;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) std::cout << ' ';
        std::cout << path[i];
    }
    std::cout << std::endl;
    return 0;
}

