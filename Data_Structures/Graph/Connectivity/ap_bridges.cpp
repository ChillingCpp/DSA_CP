struct Tarjan
{
    struct Bridge
    {
        int u = 0, v = 0;
    };
    vvi            a, sccs;
    vector<int>    disc, low, ap;
    vector<Bridge> bridge;
    int            n, t = 0;

    void init(int _n)
    {
        n = _n;
        a.resize(n + 1);
        disc.resize(n + 1);
        low.resize(n + 1);
        ap.resize(n + 1);
    }
    void ae(int u, int v)
    {
        a[u].push_back(v);
        a[v].push_back(u);
    }
    void dfs(int u, int p = -1)
    {
        low[u] = disc[u] = ++t;
        int child        = 0;
        for (int v : a[u])
        {
            if (v == p)
                continue;

            if (!disc[v])
            {
                child++;
                dfs(v, u);
                if (p != -1 && disc[u] <= low[v])  ap[u] = 1;
                if (disc[u] < low[v])  bridge.push_back({ u, v });
                low[u] = min(low[u], low[v]);
            }
            else
                low[u] = min(low[u], disc[v]);
        }
        if (p == -1 && child > 1)  ap[u] = 1;
    }
    // main code //
    void process()
    {
        for (int i = 1; i <= n; ++i)
            if (!disc[i]) dfs(i);
    }
};
