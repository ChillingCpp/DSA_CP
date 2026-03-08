    struct BCT
    {
        int         n, bccs = 1, time = 0;
        vvi         bct;
        vector<int> st, low, disc, id;
        // st : Stack chứa các đỉnh trên đường DFS hiện tại và những đỉnh chưa được gán BCC

        void build(vvi& a)
        {
            n = a.size() - 1;
            bct.resize(n + 1);
            low.resize(n + 1);
            disc.resize(n + 1);
            id.resize(n+1);
            function<void(int, int)> dfs = [&](int u, int p = -1)
            {
                low[u] = disc[u] = ++time;
                st.push_back(u);
                for (int v : a[u])
                    if (v != p)
                    {
                        if (!disc[v])
                        {
                            dfs(v, u);
                            low[u] = min(low[u], low[v]);
                            if (low[v] >= disc[u])
                            {
                                bct.emplace_back();
                                bct[u].push_back(n + bccs);
                                bct[n + bccs].push_back(u);
                                while (st.size())
                                {
                                    int x = st.back();
                                    st.pop_back();
                                    bct[x].push_back(n + bccs); /// if you dont want to connect all node then just comment 2 lines 
                                    bct[n + bccs].push_back(x);
                                    id[x] = n+bccs; 
                                    if (x == v) // phải chọn mốc kết thúc là v, nếu chọn u thì có thể sẽ bị lấy toàn bộ các subtree con u
                                        break;
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
