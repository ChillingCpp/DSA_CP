struct Seg1D
{
    vi t;
    int        n;
    Seg1D() = default;
    Seg1D(int n)
    : t(2 * n)
    , n(n)
    {
    }
    Seg1D(const vi& a)
    : t(2 * a.size())
    , n(a.size())
    {
        copy(a.begin(), a.end(), t.begin() + n);
        for (int i = n - 1; i > 0; --i)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void update(int pos, int val)
    {
        t[pos += n] += val;
        for (pos >>= 1; pos > 0; pos >>= 1)
            t[pos] = t[pos << 1] + t[pos << 1 | 1];
    }
    int query(int l, int r)
    {
        int ans = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                ans += t[l++];
            if (r & 1)
                ans += t[--r];
        }
        return ans;
    }
    Seg1D operator+(Seg1D& a)
    {
        Seg1D s(n);
        for (int i = 0; i < 2 * n; ++i)
            s.t[i] = t[i] + a.t[i];
        return s;
    }
};
struct Seg2D
{
    vector<Seg1D> t;
    int           n;
    Seg2D() = default;
    Seg2D(const vvi& a)
    : t(2 * a.size())
    , n(a.size())
    {
        for (int i = n; i < 2 * n; ++i)
            t[i] = Seg1D(a[i - n]);
        for (int i = n - 1; i > 0; --i)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void update(int x, int y, int val)
    {
        t[x += n].update(y, val);
        for (x >>= 1; x > 0; x >>= 1)
            for (int yy = (y + n) >> 1; yy > 0; yy >>= 1)
                t[x].t[yy] = t[x << 1].t[yy] + t[x << 1 | 1].t[yy];
    }
    int query(int x1, int x2, int y1, int y2)
    {
        int ans = 0;
        for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1)
        {
            if (x1 & 1)
                ans += t[x1++].query(y1, y2);
            if (x2 & 1)
                ans += t[--x2].query(y1, y2);
        }
        return ans;
    }
};
