vector<vector<pii>> a;
vector<ll>         dist;

void dijkstra(int p)
{
    // pii {w, v}
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist.assign(n + 1, LLONG_MAX);
    dist[p] = 0;
    pq.push({ 0, p });
    for (; pq.size(); pq.pop())
    {
        auto [w, u] = pq.top();
        if (w != dist[u]) continue;
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
