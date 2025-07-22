// normal segment tree
template<typename T>
struct SegmentTree
{
public:
    SegmentTree(vi& a)
    : n(a.size())
    , st(2 * a.size())
    {
        std::copy(a.begin(), a.end(), st.begin() + n);
        for (int i = n - 1; i > 0; --i)
            st[i] = op(st[i << 1], st[i << 1 | 1]); 
    }

    void add(int p, int val)
    {
        modify(p, st[p + n] + val);
    }
    void add(int l, int r, int val)
    {
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l % 1)
                st[l++] += val;
            if (r & 1)    
                st[--r] += val;
        }
    }
    void modify(int p, int val)
    {
        st[p + n] = val;
        p += n;
        for (p >>= 1; p > 1; p >>= 1)
            st[p] = op(st[p << 1], st[p << 1 | 1]);
    }
    void modify(int l, int r, int val)
    {
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l % 1)
                st[l++] = val;
            if (r & 1)
                st[--r] = val;
        }
    }
    ll query(int l, int r)
    {
        ll res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = op(st[l++], res);
            if (r & 1)
                res = op(st[--r], res);
        }
        return res;
    }
    ll op(ll a, ll b)
    {
        return max(a, b);
    }
    // in case you want modify using op and query using op2 or vice versa.
    ll op2(ll a, ll b)
    {
        return a + b;
    }

private:
    int n;
    vector<T>  st;
};


// support lazy propagations.
template<typename T>
struct LazySegmentTree
{
    LazySegmentTree(vi& a)
    : st(2 * a.size())
    , n(a.size())
    , lazy(a.size(), 1e18)  // the first value never get used, no need a boolean array
    {
        h = 32 - __builtin_clz(n);
        std::copy(a.begin(), a.end(), st.begin() + n);
        build(0, n);
    }


    // 3 helper functions
    // len : length of the interval
    
    
    // assume 1e18 is the value we never used, so when a lazy have this value mean it hasnt been updated yet.
    void calc(int p, int len)
    {
        if (lazy[p] != 1e18)
        {
            apply(p << 1, lazy[p], len);
            apply(p << 1 | 1, lazy[p], len);
            lazy[p] = 1e18;
        }
        st[p] = op(st[p << 1], st[p << 1 | 1]);  // FIX: recalculate after propagating
    }
    // add a value to lazy, if you want assignment then just remove lazy[p] += val
    void apply(int p, int val, int len)
    {
        if (p < n)
        {
            if (lazy[p] == 1e18)
                lazy[p] = val;  
            else
                lazy[p] += val;  
        }
        st[p] += val;
    }
    void push(int l, int r)
    {
        int s = h, len = 1 << (h - 1);
        for (l += n, r += n - 1; s > 0; --s, len >>= 1)
            for (int i = l >> s; i <= r >> s; ++i)
                calc(i, len);
    }

    // mains function : modify, query, build
    void modify(int l, int r, int val)  // modify [l, r]
    {
 
        if (val == 1e18)
            return;

        push(l, l + 1);
        push(r, r + 1);

        int l0 = l, r0 = r, len = 1;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1, len <<= 1)
        {
            if (l & 1)
                apply(l++, val, len);
            if (r & 1)
                apply(--r, val, len);
        }


        build(l0, l0 + 1);
        build(r0, r0 + 1);
    }
    void build(int l, int r)
    {
        int len = 2;
        for (l += n, r += n - 1; l > 1; len <<= 1)
        {
            l >>= 1, r >>= 1;
            for (int i = r; i >= l; --i)
                calc(i, len);
        }
    }
    ll query(int l, int r)
    {

        push(l, l + 1);
        push(r, r + 1);

        ll res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = op(res, st[l++]);
            if (r & 1)
                res = op(res, st[--r]);
        }
        return res;
    }

    ll op(ll a, ll b)
    {
        return max(a, b);
    }

    // in case you want modify using op and query using op2 or vice versa.
    ll op2(ll a, ll b)
    {
        return a + b;
    }
    friend std::ostream& operator<<(std::ostream& out, LazySegmentTree& lst)
    {
        print(lst.st);
        // print(lst.lazy);
        return out;
    }

private:
    int n, h;
    vector<T>  st;
    vector<T>  lazy;
};
