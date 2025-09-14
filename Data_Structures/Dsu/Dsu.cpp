struct Dsu
{
    vector<int> parent;
    vector<int> sz;
    int         compos;

    Dsu(int n)
    : parent(n)
    , sz(n, 1)
    , compos(n)
    {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x)
    {
        /// path compression + union by size : O(α(n))
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];

        /// non compression ( O(log n) because use union by size )
        for (; x != parent[x]; x = parent[x]){}
        return x;
    }
    bool unite(int x, int y)
    {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry)
            return false;

        if (sz[rx] < sz[ry])
        {
            parent[rx] = ry;
            sz[ry] += sz[rx];
        }
        else
        {
            parent[ry] = rx;
            sz[rx] += sz[ry];
        }
        compos--;
        return true;
    }
    // get total size of a component
    int getSize(int x)
    {
        return sz[find(x)];
    }
    int getComponents()
    {
        return compos;
    }
    bool check(int x, int y)
    {
        return find(x) == find(y);
    }
};
