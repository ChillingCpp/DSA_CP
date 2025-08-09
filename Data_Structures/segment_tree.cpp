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
    void modify(int p, int val)
    {
        st[p + n] = val;
        p += n;
        for (p >>= 1; p > 1; p >>= 1)
            st[p] = op(st[p << 1], st[p << 1 | 1]);
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

