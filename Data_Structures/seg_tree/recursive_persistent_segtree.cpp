struct Perseg
{
    struct Node
    {
        int l = 0, r = 0;
        int val = 0;
    };
    vector<Node> t;
    vector<int>  root; /// root[time] : id of the the time version of tree
    int          n;
    Perseg(vi& a)
    : n(a.size())
    {
        /// reserve before push back for faster
        /// can change current plus operation with any operation segment tree can support
        root.push_back(build(a, 0, n - 1));
    }
    /// public function
    void update(int time, int pos, int val)
    {
        root.push_back(update(root[time], 0, n - 1, pos, val));
    }
    int query(int time, int l, int r)
    {
        return query(root[time], 0, n - 1, l, r);
    }

    /// internal function
    int build(vi& a, int l, int r)
    {
        Node no;
        if (l == r)
        {
            no.val = a[l];
            t.push_back(no);
            return t.size() - 1;
        }
        int m  = (l + r) / 2;
        no.l   = build(a, l, m);
        no.r   = build(a, m + 1, r);
        no.val = t[no.l].val + t[no.r].val;
        t.push_back(no);
        return t.size() - 1;
    }
    int update(int cur, int l, int r, int pos, int val)
    {
        Node no = t[cur];
        if (l == r)
        {
            t.push_back(Node());
            t[t.size() - 1].val = val;
            return t.size() - 1;
        }
        int m = (l + r) / 2;
        if (pos <= m)
            no.l = update(no.l, l, m, pos, val);
        else
            no.r = update(no.r, m + 1, r, pos, val);
        no.val = t[no.l].val + t[no.r].val;
        t.push_back(no);
        return t.size() - 1;
    }
    int query(int cur, int tl, int tr, int l, int r)
    {
        if (tl > r || tr < l)
            return 0;
        if (tl >= l && tr <= r)
            return t[cur].val;
        return query(t[cur].l, tl, (tl + tr) / 2, l, r)
               + query(t[cur].r, (tl + tr) / 2 + 1, tr, l, r);
    }
};
