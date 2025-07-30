vector<vector<pair<int, int>>> a;
int                            n;  // number of vertices;

int prims()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, 0 });  // {w, u}, if 1 based then {0, 1}
    vector<bool> vis(n);
    int          res = 0;
    while (pq.size())
    {
        int u = pq.top().second;
        int w = pq.top().first;
        if (vis[u])
            continue;
        vis[u] = true;
        res += w;
        for (auto& i : a[u])
        {
            int v  = i.first;
            int w1 = i.second;
            if (vis[v])
                continue;
            pq.push({ w1, v });
        }
    }
    return res;
}
