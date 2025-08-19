
// Mo algorithms, a technique using sqrt decomposition
struct Mo
{
    ll          res = 0;
    vector<int> a, b;
    struct Query
    {
        int l, r, idx;
        ll  ord;

        Query(int l_, int r_, int idx_) : l(l_), r(r_), idx(idx_)
        {
            ord = hilbert_order(l, r, 20);
        }
        inline ll hilbert_order(int x, int y, int pow)
        {
            ////// ..... /////// see hilbert_order.cpp for more information
        }
        bool operator<(const Query& b)
        {
            return ord < b.ord;
        }
    };

    void add(int idx){
        /// adding an element to current range, O(1) or O(log n)
        res += a[idx];
    }
    void remove(int idx){
        /// remove an element from current range, O(1) or O(log n)
        res -= a[idx];
    }
    void solve()
    {
        //// ..... ///// tiền xử lí


        /// lưu truy vấn
        vector<Query> queries(q);
        for (int i = 0; i < q; ++i)
        {
            int l, r;
            cin >> l >> r;
            queries[i] = { l - 1, r - 1, i };  // convert to 0-based
        }

        sort(queries.begin(), queries.end());

        vector<ll> ans(q);
        
        int L = 0, R = -1;
        for (const auto& qr : queries)
        {
            int l = qr.l;
            int r = qr.r;

            while (R < r) add(++R);
            while (L > l) add(--L);
            while (R > r) remove(R--);
            while (L < l) remove(L++);
            ans[qr.idx] = res;
        }

        for (ll x : ans)
            cout << x << '\n';
    }
};
