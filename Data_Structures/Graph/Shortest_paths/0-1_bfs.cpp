
vector<vector<pii>> a;
vector<ll> dist;
void bfs(int src)
{
    dist[src] = 0;
    // the left push edge weight 0 and the right push edge weight 1
    for (deque<int> q{src}; q.size(); q.pop_front())
    {
        int u = q.front();
        
        for (auto [v, w] : a[u])
        {
            if (dist[v] <= dist[u] + w) continue;
            dist[v] = dist[u] + w;
            w == 0 ? q.push_front(v) : q.push_back(v);
        }
    }
}