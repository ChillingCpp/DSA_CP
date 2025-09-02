#include "dijkstra_all_pair.cpp"
#include "SPFA.cpp"

vector<vector<ll>> a, b, dist;
vector<ll> h;


/// This algorithm compute all pair shortest path in sparse graph (when V * E < V ^ 3), handle negative weight;
/// better than floyd when V > 500
void convertGraph()
{
    b = a; // copy to new graph;
    bool cycle = SPFA(1); /// compute shortest path, handle negative weight using spfa
    if (cycle) return; /// negative cycle floyd and spfa can found them
    for (int u = 1; u <= n; ++u)
        for (auto& [v, w] : b[u])
            w += h[u] - h[v]; /// weight now positive
}

void johnson()
{
    convertGraph();

    APdijkstra(); // run all pair shortest path dijkstra
}
