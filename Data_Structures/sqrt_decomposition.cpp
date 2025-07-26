const int MAXN = 1e6 + 5;
int       a[MAXN];
int       pref[MAXN];
int       freq[1 << 20];

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

    void add(int idx){
        res += freq[op(pref[idx], k)];
        freq[pref[idx]]++;
    }
    void remove(int idx){
        freq[pref[idx]]--;
        res -= freq[op(pref[idx], k)];
    }
        
    
    struct Query
    {
        int l, r, idx;
        ll  ord;

        void calcOrder(int pow = 21)
        {
            ord = hilbertOrder(l, r, pow);
        }

        inline ll hilbertOrder(int x, int y, int pow)
        {
            ll d = 0;
            for (int s = pow - 1; s >= 0; --s)
            {
                int rx = (x >> s) & 1;
                int ry = (y >> s) & 1;
                d <<= 2;
                d |= (rx << 1) | ry;
                if (ry == 0)
                {
                    if (rx == 1)
                    {
                        x = (1 << pow) - 1 - x;
                        y = (1 << pow) - 1 - y;
                    }
                    std::swap(x, y);
                }
            }

            return d;

        // true hilbert, in right order so faster than Z order
        ll  res = 0;
        int rot = 0;

        for (int p = pow; p > 0; --p)
        {
            int hp  = 1 << (p - 1);
            int seg = (x < hp ? 1 : 0) ^ (y < hp ? 1 : 2);


            static const int rotateDelta[4] = { 3, 0, 0, 1 };

            int nrot = (rot + rotateDelta[seg]) & 3;

            int nx = x & (hp - 1), ny = y & (hp - 1);
            res += seg * (1ll << (2 * p - 2));
            rot = nrot;
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
        int pow = 0;
        while ((1 << pow) < n)
            pow++;
        pref[0] = 0;
        for (int i = 0; i < n; ++i)
            pref[i + 1] = op(pref[i], a[i]);

        vector<Mo::Query> queries(q);
        for (int i = 0; i < q; ++i)
        {
            int l, r;
            cin >> l >> r;
            queries[i] = { l - 1, r, i };  // convert to 0-based for pref[l-1..r)
            queries[i].calcOrder(pow);
        }

        sort(queries.begin(), queries.end());

        vector<ll> ans(q);
        ll         res = 0;
        freq[pref[0]]  = 1;  // pref[0] = 0
        
        int L = 0, R = 0;
        for (const auto& qr : queries)
        {
            int l = qr.l;
            int r = qr.r;

            while (R < r)
            {
                ++R;
                add(R);
            }
            while (R > r)
            {
                remove(R);
                --R;
            }
            while (L < l)
            {
                remove(L);
                ++L;
            }
            while (L > l)
            {
                --L;
                add(L);
            }
            ans[qr.idx] = res;
        }

        for (ll x : ans)
            cout << x << '\n';
    }
};
