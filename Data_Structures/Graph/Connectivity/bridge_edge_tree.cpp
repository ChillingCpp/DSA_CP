struct BET
{
    struct Node
    { int disc = 0, low = 0; };
    vector<Node> vt;
    vvi          bet;
    vi           comp, bridge;
    int          n, time = 0;

    void build(vvpii& a, vpii& edges, int _n)
    {
        n = _n;
        vt.resize(n + 1);
        comp.assign(n + 1, -1);
        bridge.resize(edges.size());
        function<void(int, int)> dfs = [&](int u, int eid = -1)
        {
            vt[u].disc = vt[u].low = ++time;
            int child              = 0;
            for (auto [v, id] : a[u])
            {
                if (id == eid) continue;
                if (!vt[v].disc)
                {
                    dfs(v, id);

                    if (vt[u].disc < vt[v].low)
                        bridge[id] = 1;
                    vt[u].low = min(vt[u].low, vt[v].low);
                }
                else vt[u].low = min(vt[u].low, vt[v].disc);
            }
        };
        for (int i = 1; i <= n; ++i)
            if (!vt[i].disc)
                dfs(i, -1);

        int cid = 0;

        function<void(int)> dfsc = [&](int u)
        {
            comp[u] = cid;
            for (auto [v, id] : a[u])
            {
                if (comp[v] != -1) continue;
                if (bridge[id]) continue;  // bỏ qua cầu
                dfsc(v);
            }
        };
        for (int i = 1; i <= n; ++i)
            if (comp[i] == -1)
            {
                dfsc(i);
                cid++;
            }
        bet.resize(cid + 1);
        for (int i = 0; i < edges.size(); ++i)
            if (bridge[i])
            {
                int a = comp[edges[i].first], b = comp[edges[i].second];
                bet[a].push_back(b), bet[b].push_back(a);
            }
    }
};
