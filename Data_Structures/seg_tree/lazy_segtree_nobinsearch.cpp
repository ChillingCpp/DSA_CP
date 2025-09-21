struct Node
    {
        long long sum;
        int       len;
        Node(long long s, int sz)
        : sum(s)
        , len(sz)
        {}
    };
    struct Lazy
    {
        bool      has_set;
        long long val;
        Lazy(bool hs, long long v)
        : has_set(hs)
        , val(v)
        {}
    };
    Node op(Node a, Node b)
    {
        return Node(a.sum + b.sum, a.len + b.len);
    }
    Node in()
    {
        return {0, 0};
    }
    Node transfer(Lazy f, Node node)
    {
        if (node.len == 0)
            return node;
        if (f.has_set)
            return Node(f.val * node.len, node.len);
        return Node(node.sum + f.val * node.len, node.len);
    }
    /// nw nghĩa là lazy hiện tại, prev là lazy trước đó, hàm op này kết hợp nw và prev
    Lazy op_l(Lazy nw, Lazy prev)
    {
        if (nw.has_set)
            return nw;
        else
        {
            if (prev.has_set)
                return Lazy(true, prev.val + nw.val);
            else
                return Lazy(false, prev.val + nw.val);
        }
    }
    Lazy idl()
    {
        return {0, 0};
    }
struct Seg
{
    vector<Node> st;
    vector<Lazy> lazy;
    int          n, h;

    Seg() : Seg(0)
    Seg(int n)
    : Seg(vector<Node>(n)) {}
    Seg(const vector<Node>& a)
    {
        int sz = a.size();
        n = 1, h = 0;
        
        while (n < sz)  {  n <<= 1,  h++;  }
        
        st.resize(2 * n);
        lazy.resize(n);
        copy(a.begin(), a.end(), st.begin() + n);
        for (int i = n - 1; i > 0; --i)
            update(i);
    }
    Node all_query()
    {
        return d[1];
    }
    Node query(int l, int r)
    {
        l += n, r += n;
        push(l, r);
        Node res = idn();
        for (; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)  res = op(res, st[l++]);
            if (r & 1)  res = op(res, st[--r]);
        }
        return res;
    }
    void apply(int l, int r, Lazy val)
    {
        l += n, r += n;
        push(l, r);
        int  l1 = l, r1 = r;
        for (; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)  apply_all(l++, val);
            if (r & 1)  apply_all(--r, val);
        }
        update(l1, r1);
    }
    void apply_all(int p, Lazy val)
    {
        st[p] = transfer(st[p], val);
        if (p < n) lazy[p] = op_l(lazy[p], val);
    }
    void push(int p)
    {
        apply_all(p << 1, lazy[p]);
        apply_all(p << 1 | 1, lazy[p]);
        lazy[p] = idl();
    }
    void update(int p)
    {
        st[p] = op(st[p << 1], st[p << 1 | 1]);
    }
    void push(int l, int r)
    {
        for (int i = h; i >= 1; --i)
        {
            if (((l >> i) << i) != l)  push(l >> i);
            if (((r >> i) << i) != r)  push((r - 1) >> i);
        }
    }
    void update(int l, int r)
    {
        for (int i = 1; i <= h; ++i)
        {
            if (((l >> i) << i) != l)  update(l >> i);
            if (((r >> i) << i) != r)  update((r - 1) >> i);
        }
    }
};
/// các hàm này có thể thêm vào
void set(int p, Node x)
{
    p += size;

    push(p);
    d[p] = x;  // assign
    update(p);
}
void pushp(int p)
{
    for (int i = log; i >= 1; i--)  push(p >> i);
}
void updatep(int p)
{
    for (int i = 1; i <= log; i++) update(p >> i);
}

Node getDebug(int p)
{
    p += size;
    
    push(p, p + 1);
    return d[p];
}
