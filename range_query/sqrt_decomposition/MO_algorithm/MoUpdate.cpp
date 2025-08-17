ll hilbert_order(int x, int y, int pow)
{
    ////// ..... /////// see hilbert_order.cpp for more information
}

/// Mo algorithm with updates
struct MoUpdate
{
    ll          res = 0;
    vector<int> a, b;
    struct Query
    {
        int l, r, idx, t;
        ll  ord;

        Query(int l_, int r_, int idx_, int _t)
        : l(l_)
        , r(r_)
        , idx(idx_)
        , t(_t)
        {
            ord = hilbert_order(l, r, 20);
        }
        
        bool operator<(const Query& b)
        {
            return ord < b.ord;
        }
    };
    struct Update
    {
        int idx;
        ll  old;
        ll  val;
    };

    void add(int idx)
    {
        /// adding an element to current range, O(1) or O(log n)
        res += a[idx];
    }
    void remove(int idx)
    {
        /// remove an element from current range, O(1) or O(log n)
        res -= a[idx];
    }

    void solve()
    {
        //// ..... ///// tiền xử lí
        int n, q;
        cin >> n >> q;
        a.resize(n);
        cin >> a;
        b = a;

        /// lưu truy vấn
        vector<Query>  queries;
        vector<Update> updates;
        for (int i = 0; i < q; ++i)
        {
            int ty, u, v;
            cin >> ty >> u >> v;
            if (ty == 1)
            {
                updates.push_back({ u, b[u], v });
                b[u] = v;
            }
            else
            {
                // if 1 based then -1
                queries.push_back({ u - 1, v - 1, i, (int) updates.size() - 1 });
            }
        }

        sort(queries.begin(), queries.end());

        vector<ll> ans(q);

        int  L = 0, R = -1;
        auto update = [&](int i, int x)
        {
            if (L <= i && i <= R)
            {
                res -= a[i];
                res += x;
            }
            a[i] = x;
        };
        int t = -1;
        for (const auto& qr : queries)
        {
            int l = qr.l;
            int r = qr.r;

            while (t < qr.t)
                t++, update(updates[t].idx, updates[t].val);
            while (t > qr.t)
                update(updates[t].idx, updates[t].old), t--;

            while (R < r)
                add(++R);
            while (L > l)
                add(--L);
            while (R > r)
                remove(R--);
            while (L < l)
                remove(L++);
            ans[qr.idx] = res;
        }

        for (ll x : ans)
            cout << x << '\n';
    }
};
