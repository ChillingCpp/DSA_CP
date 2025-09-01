vector<vector<pii>> a;
vector<ll>         dist, inq, cnt;

vector<int> SPFA(int u)
{
    queue<int> q;
    q.push(u);
    inq[u]  = true;
    dist[u] = 0;

    int n = a.size();  // vertices, if 1 based then a.size() - 1
    for (; q.size(); q.pop())
    {
        int u = q.front();
        inq[u] = false;
        for (auto& [v, w] : a[u])
        {
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                if (inq[v])
                    continue;
                q.push(v);
                inq[v] = true;
                cnt[v]++;
                if (cnt[v] == n - 1)  // if relax n - 1 times mean we encountered a negative cycle
                    return { -1 };
            }
        }
    }
    return dist;
}
