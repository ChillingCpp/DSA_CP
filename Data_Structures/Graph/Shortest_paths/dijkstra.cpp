vector<vector<pii>> a;
vector<int>         dist;

void dijkstra(int u)
{
    // pii {w, v}
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[u] = 0;
    pq.push({ 0, u });
    for (; pq.size(); pq.pop())
    {
        auto [w, u] = pq.top();
        for (auto& [v, w1] : a[u])
        {
            if (dist[u] + w1 < dist[v])
            {
                dist[v] = dist[u] + w1;
                pq.push({dist[v], v});
            }
        }
    }
}
