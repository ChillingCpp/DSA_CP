    struct BET
    {
        vi   disc, low, bg, id;
        vvi  bet;
        int  t = 0, cmp = 1;
        void dfs(int u, int pid = -1)
        {
            disc[u] = low[u] = ++t;
            for (auto [v, id] : a[u])
                if (id != pid)
                {
                    if (!disc[v])
                    {
                        dfs(v, id);
                        low[u] = min(low[u], low[v]);
                        if (low[v] > disc[u])  // nếu v không có cạnh ngược để quay về tổ tiên
                                               // sớm hơn u thì (u, v) là cầu
                            bg[id] = true;
                    }
                    else
                        low[u] = min(low[u], disc[v]);
                }
        }
        void dfs2(int u, int pid = -1)
        {
            id[u] = cmp;
            for (auto [v, i] : a[u])
                if (!id[v] && i != pid && !bg[i])
                    dfs2(v, i);
        }
        void build()
        {
            disc.resize(n + 1);
            low.resize(n + 1);
            bg.resize(m + 1);
            id.resize(n + 1);

            for (int i = 0; i < n; ++i)
                if (!disc[i])
                    dfs(i, -1);
            for (int i = 0; i < n; ++i)
                if (!id[i])
                    dfs2(i, -1), cmp++;
            
            bet.resize(cmp + 1);
            for (int u = 1; u <= n; ++u)
                for (auto [v, i] : a[u])
                    if (u < v && id[u] != id[v])
                        bet[id[u]].push_back(id[v]), bet[id[v]].push_back(id[u]);
        }
    };
