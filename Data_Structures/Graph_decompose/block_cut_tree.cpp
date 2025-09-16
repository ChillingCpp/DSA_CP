struct BCT
{
    int         n, bccs = 1, time = 0;
    vvi         bct;
    vector<int> st, low, disc;

    void build(vvi& a)
    {
        n = a.size() - 1;
        bct.resize(n + 1);
        function<void(int, int)> dfs = [&](int u, int p = -1)
        {
            low[u] = disc[u] = ++time;
            st.push_back(u);
            for (int v : a[u])
            {
                if (v == p)  
                    continue;
                if (!disc[v])
                {
                    dfs(v, u);
                    low[u] = min(low[u], low[v]);
                    if (low[v] >= disc[u])
                    {
                        bct.emplace_back({});
                        bct[u].push_back(n + bccs);
                        bct[n + bccs].push_back(u);
                        while (st.size())
                        {
                            int x = st.back();
                            st.pop_back();
                            bct[x].push_back(n + bccs);
                            bct[n + bccs].push_back(x);
                            if (x == v) break;
                        }
                        bccs++;
                    }
                }
                else
                    low[u] = min(low[u], disc[v]);
            }
        };
        for (int i = 1; i <= n; ++i)
            if (!disc[i])
                dfs(i, -1);
    }
};
