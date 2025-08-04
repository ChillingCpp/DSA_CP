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
struct Lazysegtree
{
    vector<ll> st, lazy;
    int        n, h;
    Lazysegtree(vector<int>& a)
    : st(2 * a.size())
    , n(a.size())
    , lazy(a.size())
    {
        h = 32 - __builtin_clz(n);
        std::copy(a.begin(), a.end(), st.begin() + n);
        for (int i = n - 1; i > 0; --i)
            st[i] = op1(st[i << 1], st[i << 1 | 1]);
    }
    void modify(int l, int r, int value)
    {
        if (value == 0)
            return;
        r++;  // work with [l, r]
        push(l);
        push(r - 1);
        int l0 = l, r0 = r, len = 1;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1, len <<= 1)
        {
            if (l & 1)
                apply(l++, value, len);
            if (r & 1)
                apply(--r, value, len);
        }
        build(l0);
        build(r0 - 1);
    }

    int query(int l, int r)
    {
        r++;  // work with [l, r]
        push(l);
        push(r - 1);
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = op1(res, st[l++]);
            if (r & 1)
                res = op1(res, st[--r]);
        }
        return res;
    }

private:
    ll op1(ll a, ll b)
    {
        return a + b;
    }
    ll op2(ll a, ll b)
    {
        return max(a, b);
    }
    void calc(int p, int len)
    {
        if (lazy[p] == 1e18)
            st[p] = op1(st[p << 1], st[p << 1 | 1]);
        else
            st[p] = lazy[p] * len;  // if range sum
    }

    void apply(int p, int value, int len)
    {
        st[p] = value * len;  // if range sum
        if (p < n)
            lazy[p] = value;  // assign, if addition or subtraction then just do lazy[p] += value or
                              // lazy[p] -= value;
    }
    void build(int l)
    {
        for (int p = (l + n) >> 1, len = 2; p > 1; len <<= 1)
            calc(p, len);
    }

    void push(int l)
    {
        for (int s = h, len = 1 << (h - 1); s > 0; --s, len >>= 1)
        {
            int i = (l + n) >> s;
            if (lazy[i] != 1e18)
            {
                apply(i << 1, lazy[i], len);
                apply(i << 1 | 1, lazy[i], len);
                lazy[i] = 1e18;
            }
        }
    }
    friend std::ostream& operator<<(std::ostream& out, Lazysegtree& lst)
    {
        print(lst.st);
        // print(lst.lazy);
        return out;
    }
};
