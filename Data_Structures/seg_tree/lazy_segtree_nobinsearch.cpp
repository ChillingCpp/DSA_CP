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

    Node id_node()
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
    Lazy op_lazy(Lazy nw, Lazy prev)
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
    Lazy id_lazy()
    {
        return {0, 0};
    }

struct lazy_segtree
{
public:
    lazy_segtree()
    : lazy_segtree(0)
    {
    }
    explicit lazy_segtree(int n)
    : lazy_segtree(std::vector<Node>(n, id_node()))
    {
    }
    explicit lazy_segtree(const std::vector<Node>& v)
    : _n(int(v.size()))
    {
        size = (int) bit_ceil((unsigned int) (_n));
        log  = __builtin_ctz(size);
        d    = std::vector<Node>(2 * size, id_node());
        lz   = std::vector<Lazy>(size, id_lazy());
        std::copy(v.begin(), v.end(), d.begin() + size);

        for (int i = size - 1; i >= 1; i--)
            update(i);
    }

    void set(int p, Node x)
    {
        p += size;

        push(p, p + 1);
        d[p] = x;  // assign
        update(p, p + 1);
    }
    
    Node query(int l, int r)
    {
        if (l == r)
            return id_node();

        l += size;
        r += size;
        push(l, r);

        Node ans = id_node();
        for (; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                ans = op(ans, d[l++]);
            if (r & 1)
                ans = op(ans, d[--r]);
        }
        return ans;
    }

    Node all_query()
    {
        return d[1];
    }

    void apply(int l, int r, Lazy f)
    {
        if (l == r)
            return;

        l += size;
        r += size;

        push(l, r);

        for (int l2 = l, r2 = r; l2 < r2; l2 >>= 1, r2 >>= 1)
        {
            if (l2 & 1)
                all_apply(l2++, f);
            if (r2 & 1)
                all_apply(--r2, f);
        }

        update(l, r);
    }
private:
    int               _n, size, log;
    std::vector<Node> d;
    std::vector<Lazy> lz;

    void all_apply(int k, Lazy f)
    {
        d[k] = transfer(f, d[k]);  /// apply to node
        if (k < size)              /// if still in parent then propagate lazy
            lz[k] = op_lazy(f, lz[k]);
    }
    void push(int l, int r)
    {
        for (int i = log; i >= 1; i--)
        {
            if (((l >> i) << i) != l)
                push(l >> i);
            if (((r >> i) << i) != r)
                push((r - 1) >> i);
        }
    }
    void update(int l, int r)
    {
        for (int i = 1; i <= log; i++) /// update range [l, r)
        {
            if (((l >> i) << i) != l)
                update(l >> i);
            if (((r >> i) << i) != r)
                update((r - 1) >> i);
        }   
    }

    void update(int k)
    {
        d[k] = op(d[2 * k], d[2 * k + 1]);  /// merge
    }
    void push(int k)
    {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id_lazy();
    }
    int bit_ceil(unsigned x)
    {
        if (x <= 1)
            return 1;
        return 1u << (32 - __builtin_clz(x - 1));
    }
};

/// các hàm này có thể thêm vào
void pushp(int p)
{
    for (int i = log; i >= 1; i--)
        push(p >> i);
}
void updatep(int p)
{
    for (int i = 1; i <= log; i++)
        update(p >> i);
}

Node getDebug(int p)
{
    p += size;
    
    push(p, p + 1);
    return d[p];
}
