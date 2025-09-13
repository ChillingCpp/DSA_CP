struct Tarjan
{
    struct Node
    {
        int low = 0, disc = 0, ap = 0;
    };
    struct Bridge
    {
        int u = 0, v = 0;
    };
    vvi            a, sccs;
    vector<Node>   vt;
    vector<Bridge> bridge;
    int            n, t = 0;

    void init(int _n)
    {
        n = _n;
        a.resize(n);
        vt.resize(n);
    }
    void ae(int u, int v)
    {
        a[u].push_back(v);
        a[v].push_back(u);
    }
    void tarjan(int u, int p)
    {
        vt[u].low = vt[u].disc = ++t;

        int child = 0;

        for (int v : a[u])
        {
            if (v == p)
                continue;

            if (!vt[v].disc)
            {
                child++;
                tarjan(v, u);
                /// if the v is in the component of u or v is discovery earlier than u then u is the
                /// articular point
                if (p != -1 && vt[u].disc <= vt[v].low)
                    vt[u].ap = 1;
                // if (disc[v] == low[u]) then we have encounterd a cycle, if we disconnected the
                // edge {u, v} then nothing will happened
                if (vt[u].disc < vt[v].low)  //
                    bridge.push_back({ u, v });

                vt[u].low = min(vt[u].low, vt[v].low);
            }
            else
                vt[u].low = min(vt[u].low, vt[v].disc);
        }
        if (p == -1 && child > 1)
            vt[u].ap = 1;
    }
    // main code //
    void process()
    {
        for (int i = 1; i <= n; ++i)
            if (!vt[i].disc)
                tarjan(i, i);
    }
};
