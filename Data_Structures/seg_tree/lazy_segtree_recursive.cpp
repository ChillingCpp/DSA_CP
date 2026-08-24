struct Node
{
    ll  val = 0;
    int len = 1;
};
struct Lazy
{
    ll val = 0;
};
Lazy op_l(Lazy n, Lazy o)
{
    return { n.val + o.val };
}
Node tf(Node n, Lazy l)
{
    return { n.val + l.val * n.len };
};
Node op(Node a, Node b)
{
    return { a.val + b.val, a.len + b.len };
};
Node idn()
{
    return { 0, 0 };
}
Lazy idl()
{
    return Lazy();
}
struct LazySegtree
{
    vector<Node> st;
    vector<Lazy> lz;
    int          n;
    LazySegtree() = default;
    LazySegtree(int n)
    : st(4 * n)
    , lz(4 * n)
    , n(n)
    {
    }
    LazySegtree(const vi& a)
    : st(4 * a.size())
    , lz(4 * a.size())
    , n(a.size())
    {
        build(a, 1, 0, n - 1);
    }
    void apply(int v, Lazy l)
    {
        st[v] = tf(st[v], l);
        lz[v] = op_l(lz[v], l);
    }
    void push(int v)
    {
        apply(v << 1, lz[v]);
        apply(v << 1 | 1, lz[v]);
        lz[v] = idl();
    }
    void build(const vi& a, int v, int l, int r)
    {
        if (l > r)
            return;
        if (l == r)
        {
            st[v].val = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, v << 1, l, m);
        build(a, v << 1 | 1, m + 1, r);
        st[v] = op(st[v << 1], st[v << 1 | 1]);
    }
    void updateRange(Lazy val, int v, int tl, int tr, int l, int r)
    {
        if (tl > r || tr < l)
            return;
        if (tl >= l && tr <= r)
        {
            apply(v, val);
            return;
        }
        push(v);
        int m = (tl + tr) / 2;
        updateRange(val, v << 1, tl, m, l, r);
        updateRange(val, v << 1, m + 1, tr, l, r);
        st[v] = op(st[v << 1], st[v << 1 | 1]);
    }
    Node query(int v, int tl, int tr, int l, int r)
    {
        if (tl > r || tr < l)
            return idn();
        if (tl >= l && tr <= r)
            return st[v];
        push(v);
        int m = (tl + tr) / 2;
        return op(query(v * 2, tl, m, l, r), query(v * 2 + 1, m + 1, tr, l, r));
    }
};
