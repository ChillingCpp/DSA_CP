// Mo algorithms, a technique using sqrt decomposition
struct Mo
{
    // work with any operation.
    ll op(ll a, ll b)
    {
        return a ^ b;
    }

    // eg for some op have this properties : a[i] + a[j] = k -> a[i] = k - a[j];
    ll op2(ll a, ll b)
    {
        return a - b;
    }

    void add(ll res, int idx){
        /// adding an element to current range, O(1) or O(log n)
    }
    void remove(ll res, int idx){
        /// remove an element from current range, O(1) or O(log n)
    }
        
    
    struct Query
    {
        int l, r, idx;
        ll  ord;

        Query(int l_, int r_, int idx_) : l(l_), r(r_), idx(idx_)
        {
            ord - hilbert_order(l, r, 20);
        }
        inline ll hilbert_order(int x, int y, int pow)
        {
            // true hilbert, in right order so faster than Z order
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
    void solve()
    {
        int n, q, k;
        cin >> n >> q >> k;

        for (int i = 0; i < n; ++i)
            cin >> a[i];

        // calc something

        vector<Mo::Query> queries(q);
        for (int i = 0; i < q; ++i)
        {
            int l, r;
            cin >> l >> r;
            queries[i] = { l - 1, r - 1, i };  // convert to 0-based
        }

        sort(queries.begin(), queries.end());

        vector<ll> ans(q);
        ll         res = 0;
        
        int L = 0, R = 0;
        for (const auto& qr : queries)
        {
            int l = qr.l;
            int r = qr.r;

            while (R < r)
            {
                ++R;
                add(res, R);
            }
            while (R > r)
            {
                remove(res, R);
                --R;
            }
            while (L < l)
            {
                remove(res, L);
                ++L;
            }
            while (L > l)
            {
                --L;
                add(res, L);
            }
            ans[qr.idx] = res;
        }

        for (ll x : ans)
            cout << x << '\n';
    }
};
