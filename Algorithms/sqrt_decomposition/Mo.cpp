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
            ll  res = 0;
            int rot = 0;

            for (int p = pow; p > 0; --p)
            {
                int hp  = 1 << (p - 1);
                int seg = (x < hp ? 1 : 0) ^ (y < hp ? 1 : 2);
                
                static const int rotateDelta[4] = { 3, 0, 0, 1 };

                rot = (rot + rotateDelta[seg]) & 3;

                int nx = x & (hp - 1), ny = y & (hp - 1);
                res += seg * (1ll << (2 * p - 2));
                switch (seg)
                {
                    case 0:
                        x = ny;
                        y = nx;
                    break;
                    case 3:
                        x = hp - ny - 1;
                        y = hp - nx - 1;
                    break;
                    default:
                        x = nx;
                        y = ny;
                    break;
                }
            }
            return res;
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


// Mo algorithms, a technique using sqrt decomposition
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
        inline ll hilbert_order(int x, int y, int pow)
        {
            ll  res = 0;
            int rot = 0;

            for (int p = pow; p > 0; --p)
            {
                int hp  = 1 << (p - 1);
                int seg = (x < hp ? 1 : 0) ^ (y < hp ? 1 : 2);

                static const int rotateDelta[4] = { 3, 0, 0, 1 };

                rot = (rot + rotateDelta[seg]) & 3;

                int nx = x & (hp - 1), ny = y & (hp - 1);
                res += seg * (1ll << (2 * p - 2));
                switch (seg)
                {
                    case 0:
                        x = ny;
                        y = nx;
                        break;
                    case 3:
                        x = hp - ny - 1;
                        y = hp - nx - 1;
                        break;
                    default:
                        x = nx;
                        y = ny;
                        break;
                }
            }
            return res;
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

/// Mo on tree or graph require some thing to turn these queries into a flat array, making range queries useful
/// euler tour convert a tree into an array

