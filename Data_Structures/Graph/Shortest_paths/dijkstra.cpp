vector<vector<pii>> a;
vector<int>         dist;

void dijkstra(int u)
{
    // pii {w, v}
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[u] = 0;
    pq.push({ 0, u });
    while (pq.size())
    {
        int u = pq.top().second;
        int w = pq.top().first;
        if (dist[u] != w)
            continue;
        for (auto& p : a[u])
        {
            int v  = p.first;
            int w1 = p.second;
            if (dist[u] + w1 < dist[v])
            {
                dist[v] = dist[u] + w1;
            }
        }
    }
}
