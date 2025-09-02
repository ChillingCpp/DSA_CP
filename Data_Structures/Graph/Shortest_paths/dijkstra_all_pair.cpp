// O(VE log V), but in some case its better than floyd because VE < V^3, for eg : V = 1000, E = 5000

vector<vector<pii>> a;
vector<vector<ll>> dist;

void dijkstra(int p)
{
    // pii {w, v}
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    dist[p][p] = 0;
    pq.push({ 0, p });
    for (; pq.size(); pq.pop())
    {
        auto [w, u] = pq.top();
        if (w != dist[p][u]) continue;
        for (auto& [v, w1] : a[u])
        {
            if (dist[p][u] + w1 < dist[p][v])
            {
                dist[p][v] = dist[p][u] + w1;
                pq.push({dist[p][v], v});
            }
        }
    }
}


void APdijkstra()
{
    dist.assign(n + 1, vector<ll>(n + 1, LLONG_MAX));
    for (int i = 1; i <= n; ++i) 
        dijkstra(i);
}   