struct Dsu
{
    vector<int> p;
    vector<int> sz;
    // nxt[i] được định nghĩa là vị trí kế tiếp về bên phải chưa được xử lí
    // ban đầu nxt[i] = i do i chưa được xử lí
    vector<int> nxt;  // jump pointer, this version now only support linear
    int         compos;

    Dsu(int n)
    : p(n)
    , sz(n, 1)
    , compos(n)
    , nxt(n + 1)
    {
        iota(p.begin(), p.end(), 0);
        iota(nxt.begin(), nxt.end(), 0);
    }
    int find(int x)
    {
        /// path compression + union by size : O(α(n))
        if (x == p[x])
            return x;
        return p[x] = find(p[x]);

        /// non compression ( O(log n) because use union by size )
        for (; x != p[x]; x = p[x])
        {
        }
        return x;
    }
    int findnxt(int x)
    {
        if (x == nxt[x])
            return x;
        return nxt[x] = find(nxt[x]);
    }
    bool unite(int x, int y)
    {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry)
            return false;

        if (sz[x] < sz[y])
            swap(x, y);
        p[y] = x;
        sz[x] += sz[y];
        return true;
    }
    /// nxt pointer support subarray query
    void urange(int l, int r)
    {
        for (int v = findnxt(l); v <= r; v = findnxt(v))
        {
            /// do something
            p[v] = v + 1;
        }
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
