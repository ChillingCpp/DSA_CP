struct LazySegtree
{
    vi  st;
    vi  lz;
    int n;
    LazySegtree() = default;
    LazySegtree(int n)
    : st(4 * n)
    , lz(n)
    {
    }
    LazySegtree(const vi& a)
    : st(4 * a.size())
    , lz(4 * a.size())
    , n(a.size())
    {
    }
    void apply(int v, int len, int val)
    {
        st[v] += len * val;
        lz[v] += val;
    }
    void push(int v, int l, int r)
    {
        apply(v << 1, r - l + 1, lz[v]);
        apply(v << 1 | 1, r - l + 1, lz[v]);
        lz[v] = 0;
    }
    void build(const vi& a, int v, int l, int r)
    {
        if (l > r)
            return;
        if (l == r)
        {
            st[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, v << 1, l, m);
        build(a, v << 1 | 1, m + 1, r);
        st[v] = st[v << 1] + st[v << 1 | 1];
    }
    void update(int val, int v, int l, int r, int pos)
    {
        if (l > r)
            return;
        if (l == r)
        {
            st[v] = val;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m)
            update(val, v << 1, l, m, pos);
        else
            update(val, v << 1 | 1, m + 1, r, pos);
        st[v] = st[v << 1] + st[v << 1 | 1];
    }
    void updateRange(int val, int v, int tl, int tr, int l, int r)
    {
        if (tl > r || tr < l)
            return;
        if (tl >= l && tr <= r)
        {
            apply(v, tr - tl + 1, val);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        updateRange(val, v << 1, tl, m, l, r);
        updateRange(val, v << 1, m + 1, tr, l, r);
        st[v] = st[v << 1] + st[v << 1 | 1];
    }
    int query(int v, int tl, int tr, int l, int r)
    {
        if (tl > r || tr < l)
            return 0;
        if (tl >= l && tr <= r)
            return st[v];
        push(v, tl, tr);
        int m = (tl + tr) / 2;
        return query(v * 2, tl, m, l, r) + query(v * 2 + 1, m + 1, tr, l, r);
    }
};
