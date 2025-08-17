
/// ý tưởng : chia mảng A thành ceil(sqrt(n)) mảng có độ dài sqrt(n)

//// có kết hợp kĩ thuật lazy propagation tương tự segment tree (apply lazy vào các block

struct SqrtDecomposition{

    int n;
    int S;
    vector<ll> b;
    vector<ll> a;
    SqrtDecomposition(vector<ll> &v) : n(v.size()), a(v)
    {
        S = (int) sqrt(n) + 1;
        b.resize(S);
        for (int i = 0; i < n; ++i)
            b[i / S] += a[i];
    }
    
    /// range query - Immutable
    ll query(int l, int r){

        int c_l = l / S, c_r = r / S;
        ll sum = 0;
        if (c_l == c_r) for (int i = l; i <= r; ++i) sum += a[i];
        else
        { 
            for (int i = l; i < (c_l + 1) * S; ++i) sum += a[i]; /// [l....last_c_l]
            for (int i = c_r*S; i <= r; ++i) sum += a[i]; // [first....r]
            for (int i = c_l + 1; i < c_r; ++i) sum += b[i]; // calculate the block fit in range
        }
        return sum;
    }
};

// range query - range update
struct SqrtLazy
{
    int        n;
    int        S;
    vector<ll> b;
    vector<ll> a;
    vector<ll> lazy;
    SqrtLazy(vector<ll>& v)
    : n(v.size())
    , a(v)
    {
        S = (int) sqrt(n) + 1;
        b.resize(S);
        lazy.resize(S);
        for (int i = 0; i < n; ++i)
            b[i / S] += a[i];
    }
    int blocksize(int i)
    {
        int l = i * S;
        int r = min(n - 1, (i + 1) * S - 1);
        return r - l + 1;
    }
    void apply(int bid)
    {
        b[bid] = 0;
        int l  = bid * S;
        int r  = min(n - 1, (bid + 1) * S - 1);
        for (int i = l; i <= r; ++i)
            a[i] += lazy[bid];

        for (int i = l; i <= r; ++i)
            b[bid] += a[i];

        lazy[bid] = 0;
    }
    void addlazy(int c_l, int c_r, ll val)
    {
        for (int i = c_l; i <= c_r; ++i)
            lazy[i] += val;
    }
    void manual_update(int l, int r, ll val)
    {
        int c = l / S;
        for (int i = l; i <= r; ++i)
        {
            a[i] += val;
            b[c] += val;
        }
    }
    void update(int l, int r, ll val)
    {
        int c_l = l / S;
        int c_r = r / S;
        if (c_l == c_r)
        {
            apply(c_l);
            manual_update(l, r, val);
        }
        else
        {
            apply(c_l);
            apply(c_r);

            addlazy(c_l + 1, c_r - 1, val);

            manual_update(l, min(n - 1, (c_l + 1) * S - 1), val);
            manual_update(c_r * S, r, val);
        }
    }
    /// range query - Immutable
    ll query(int l, int r)
    {
        int c_l = l / S, c_r = r / S;
        ll  sum = 0;
        if (c_l == c_r)
        {
            apply(c_l);
            for (int i = l; i <= r; ++i)
                sum += a[i];
        }
        else
        {
            apply(c_l);
            apply(c_r);
            for (int i = l; i < (c_l + 1) * S; ++i)
                sum += a[i];  /// [l....last_c_l]
            for (int i = c_r * S; i <= r; ++i)
                sum += a[i];  // [first....r]
            for (int i = c_l + 1; i < c_r; ++i)
                sum += (b[i] + lazy[i] * blocksize(i));  // calculate the block fit in range
        }
        return sum;
    }
};