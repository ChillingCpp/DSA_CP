struct BET
{
    vector<int> disc, low, comp, ins, id;
    stack<int>  st;
    vvi bet;
    int n, time = 0, cmp = 0;
    /// edge : {to, id}. id is when we get input
    void build(vvi& a, vpii& ed, int _n)
    {
        n = _n;
        disc.resize(n + 1), low.resize(n + 1);
        comp.resize(n + 1), ins.resize(n + 1);
        id.resize(n + 1);
        function<void(int, int)> dfs = [&](int u, int p = -1)
        {
            disc[u] = low[u] = ++time;
            ins[u]           = 1;
            st.push(u);
            for (auto v : a[u])
            {
                if (v == p) continue;
                if (!disc[v])
                {
                    dfs(v, u);
                    low[u] = min(low[u], low[v]);
                }
                else if (ins[v])
                    low[u] = min(low[u], disc[v]);
            }
            if (low[u] == disc[u])
            {
                cmp++;
                while (st.size())
                {
                    int v = st.top();
                    st.pop();
                    ins[v] = 0;
                    id[v]  = cmp;
                    if (v == u)
                        break;
                }
            }
        };
        for (int i = 1; i <= n; ++i)
            if (!disc[i])
                dfs(i, -1);

        bet.resize(cmp + 1);
        for (auto e : ed)
            if (id[e.first] != id[e.second])
            {
                bct[id[e.first]].push_back(id[e.second]);
                bct[id[e.second]].push_back(id[e.first]);
            }
    }
};
