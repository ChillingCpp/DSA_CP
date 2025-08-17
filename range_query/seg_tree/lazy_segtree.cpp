struct lazy_segtree
{
public:
    struct Node
    {
        long long sum;
        int       len;
        Node()
        : sum(0)
        , len(0)
        {
        }
        Node(long long s, int sz)
        : sum(s)
        , len(sz)
        {
        }
    };

    struct Lazy
    {
        bool      has_set;
        long long val;
        Lazy()
        : has_set(false)
        , val(0)
        {
        }
        Lazy(bool hs, long long v)
        : has_set(hs)
        , val(v)
        {
        }
    };

    Node op(Node a, Node b)
    {
        return Node(a.sum + b.sum, a.len + b.len);
    }

    Node id_node()
    {
        return Node();
    }

    Node transfer(Lazy f, Node node)
    {
        if (node.len == 0)
            return node;
        if (f.has_set)
        {
            return Node(f.val * node.len, node.len);
        }
        else
        {
            return Node(node.sum + f.val * node.len, node.len);
        }
    }

    /// nw nghĩa là lazy hiện tại, prev là lazy trước đó, hàm op này kết hợp nw và prev
    Lazy op_lazy(Lazy nw, Lazy prev)
    {
        if (nw.has_set)
        {
            return nw;
        }
        else
        {
            if (prev.has_set)
            {
                return Lazy(true, prev.val + nw.val);
            }
            else
            {
                return Lazy(false, prev.val + nw.val);
            }
        }
    }
    Lazy id_lazy()
    {
        return Lazy();
    }
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
        for (int i = 0; i < _n; i++)
            d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--)
        {
            update(i);
        }
    }

    void set(int p, Node x)
    {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }

    Node get(int p)
    {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        return d[p];
    }

    Node query(int l, int r)
    {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r)
            return id_node();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--)
        {
            if (((l >> i) << i) != l)
                push(l >> i);
            if (((r >> i) << i) != r)
                push((r - 1) >> i);
        }

        Node sml = id_node(), smr = id_node();
        while (l < r)
        {
            if (l & 1)
                sml = op(sml, d[l++]);
            if (r & 1)
                smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    Node all_query()
    {
        return d[1];
    }

    void apply(int p, Lazy f)
    {
        assert(0 <= p && p < _n);
        p += size;
        // first push all to child
        for (int i = log; i >= 1; i--)
            push(p >> i);
        
        // apply lazy to leaf
        d[p] = transfer(f, d[p]);

        // update again
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }
    void apply(int l, int r, Lazy f)
    {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r)
            return;

        l += size;
        r += size;

        /// first push all node in interval [l, r) to child node
        for (int i = log; i >= 1; i--)
        {
            if (((l >> i) << i) != l)
                push(l >> i);
            if (((r >> i) << i) != r)
                push((r - 1) >> i);
        }


        /// apply lazy to node in range [l, r)
        {
            int l2 = l, r2 = r;
            while (l < r)
            {
                if (l & 1)
                    all_apply(l++, f);
                if (r & 1)
                    all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        /// update the tree in range [l, r)
        for (int i = 1; i <= log; i++)
        {
            if (((l >> i) << i) != l)
                update(l >> i);
            if (((r >> i) << i) != r)
                update((r - 1) >> i);
        }
    }

    /// these below are binary search on segment tree, we need to remember 
    template<bool (*g)(Node)>
    int max_right(int l)
    {
        return max_right(l, [](Node x) { return g(x); });
    }
    template<class G>
    int max_right(int l, G g)
    {
        assert(0 <= l && l <= _n);
        assert(g(id_node()));
        if (l == _n)
            return _n;
        l += size;
        /// push all child at index l
        for (int i = log; i >= 1; i--)
            push(l >> i);
        Node sm = id_node();
        
        // binary search, the left subtree is where answer is still valid
        do
        {
            while (l % 2 == 0)
                l >>= 1;
            if (!g(op(sm, d[l])))
            {
                while (l < size)
                {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) /// check if right subtree is valid then go to right, do op to currrent node sm
                    {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template<bool (*g)(Node)>
    int min_left(int r)
    {
        return min_left(r, [](Node x) { return g(x); });
    }
    template<class G>
    int min_left(int r, G g)
    {
        assert(0 <= r && r <= _n);
        assert(g(id_node()));
        if (r == 0)
            return 0;
        r += size;
        for (int i = log; i >= 1; i--)
            push((r - 1) >> i);
        Node sm = id_node();
        do
        {
            r--;
            while (r > 1 && (r % 2))
                r >>= 1;
            if (!g(op(d[r], sm)))
            {
                while (r < size)
                {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) /// same as above but change l to r
                    {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    int               _n, size, log;
    std::vector<Node> d;
    std::vector<Lazy> lz;

    void update(int k)
    {
        d[k] = op(d[2 * k], d[2 * k + 1]); /// merge
    }
    void all_apply(int k, Lazy f)
    {
        d[k] = transfer(f, d[k]); /// apply to node
        if (k < size) /// if still in parent then propagate lazy
            lz[k] = op_lazy(f, lz[k]); 
    }
    void push(int k)
    {

        /// apply lazy to children and set to 0 (have propagated)
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