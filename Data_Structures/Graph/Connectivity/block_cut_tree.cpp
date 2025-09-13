struct BCC
{
    struct Node { int disc = 0, low = 0, ap = 0; };
    vector<Node> vt;
    vvi          bct, comp;
    stack<pii>   st;
    int          n, time = 0;

    void getcomp(pii ed)
    {
        vi c;
        while (st.size())
        {
            auto e = st.top();
            st.pop();
            c.push_back(e.first);
            c.push_back(e.second);
            if (e == ed) break;
        }
        comp.push_back(c);
    }

    void build(vvi& a, int _n)
    {
        n = _n;
        vt.resize(n + 1);
        function<void(int, int)> dfs = [&](int u, int p = -1)
        {
            vt[u].disc = vt[u].low = ++time;
            int child              = 0;
            for (int v : a[u])
            {
                if (v == p) continue;
                if (!vt[v].disc)
                {
                    st.emplace(u, v);
                    child++;
                    dfs(v, u);

                    if (p != -1 && vt[u].disc <= vt[v].low)
                    {
                        vt[u].ap = 1;
                        getcomp({ u, v }); // get component when encoutered a articulation point
                    }
                    vt[u].low = min(vt[u].low, vt[v].low);
                }
                else
                {
                    st.emplace(u, v);
                    vt[u].low = min(vt[u].low, vt[v].disc);
                }
            }
            if (p == -1 && child > 1) vt[u].ap = 1;
        };
        for (int i = 1; i <= n; ++i)
        {
            if (!vt[i].disc)
            {
                dfs(i, -1);
                if (st.size()) getcomp(st.top()); // get all left to a componenet
            }
        }
        int cnt   = comp.size();
        int total = n + 1 + cnt;
        bct.resize(total + 1);
        for (int i = 0; i < cnt; ++i)
        {
            int node = n + i + 1;
            for (int v : comp[i])
            {
                if (vt[v].ap)
                {
                    bct[v].push_back(node);
                    bct[node].push_back(v);
                }
            }
        }
    }
};
