vector<vector<pii>> a;
vector<int>         dist, vis, cnt;

vector<int> bellman_ford(int u)
{
    queue<int> q;
    q.push(u);
    vis[u]  = true;
    dist[u] = 0;

    int n = a.size();  // vertices, if 1 based then a.size() - 1
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (auto i : a[u])
        {
            int v = i.first;
            int w = i.second;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                if (vis[v])
                    continue;
                q.push(v);
                vis[v] = true;
                cnt[v]++;
                if (cnt[v] == n - 1)  // if relax n - 1 times mean we encountered a negative cycle
                    return { -1 };
            }
        }
    }
    return dist;
}
