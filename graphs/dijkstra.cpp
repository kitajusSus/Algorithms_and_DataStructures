#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>

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
            file >> x >> y; // coordinates, unused by Dijkstra but kept for compatibility
            g.coords[i] = {x, y};
        }
        for (int i = 0; i < m; ++i) {
            int u, v;
            double w;
            file >> u >> v >> w;
            g.adj[u].push_back({v, w});
            g.adj[v].push_back({u, w}); // assume undirected graph
        }
        return g;
    }
};

std::vector<double> dijkstra(const Graph &g, int start) {
    const double INF = std::numeric_limits<double>::infinity();
    std::vector<double> dist(g.adj.size(), INF);
    dist[start] = 0.0;
    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0.0, start});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (const auto &e : g.adj[u]) {
            if (dist[e.to] > d + e.weight) {
                dist[e.to] = d + e.weight;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " graph.txt start" << std::endl;
        return 1;
    }
    Graph g = Graph::loadFromFile(argv[1]);
    int start = std::stoi(argv[2]);
    auto dist = dijkstra(g, start);
    for (size_t i = 0; i < dist.size(); ++i) {
        std::cout << i << ": " << dist[i] << '\n';
    }
    return 0;
}

