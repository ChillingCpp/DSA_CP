struct DSU
{
    vi                    par, sz;
    vector<pair<ll&, ll>> h; // history
    DSU()                     = default;
    DSU(int n)
    : par(n)
    , sz(n, 1)
    {
        iota(par.begin(), par.end(), 0);
    }
    /// not using path compression
    int find(int x)
    {
        return (x == par[x] ? x : find(par[x]));
    }
    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (sz[x] < sz[y])
            swap(x, y);
        h.push_back({ par[y], par[y] });
        h.push_back({ sz[x], sz[x] });
        par[y] = x;
        sz[x] += sz[y];
    }
    int snapshot()
    {
        return h.size();
    }
    void roll(int until)
    {
        int u = 0;
        while (h.size() > until)
        {
            h.back().first = h.back().second;
            h.pop_back();
            u++;
            if (u % 2 == 0)
                cmp++;
        }
    }
    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
    ll size(ll x)
    {
        return sz[find(x)];
    }
};
