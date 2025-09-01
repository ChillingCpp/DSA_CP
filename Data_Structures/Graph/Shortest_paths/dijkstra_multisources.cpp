vector<vector<pii>> a;
vector<ll> dist;
void dijkstra(vector<int> src)
{
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    for (auto s : src){
        pq.push({0, s});
        dist[s] = 0;
    } 
    for (; pq.size(); pq.pop())
    {
        auto [d, u] = pq.top();
        if (d >= dist[u]) continue;
        for (auto& [v, w] : a[u])
        {
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

}