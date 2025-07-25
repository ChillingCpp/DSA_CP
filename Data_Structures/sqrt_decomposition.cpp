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
    int L = 0, R = 0;
    struct Query
    {
        int l, r, idx;
        ll  ord;

        void calcOrder(int pow = 21)
        {
            ord = hilbertOrder(l, r, pow);
        }

        ll hilbertOrder(int x, int y, int pow)
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

            //// recursion
            // if (pow == 0)
            //     return 0;
            // int hpow                        = 1 << (pow - 1);
            // int seg                         = (x < hpow ? 0 : 1) | (y < hpow ? 0 : 2);
            // seg                             = (seg + rot) & 3;
            // static const int rotateDelta[4] = { 3, 0, 0, 1 };
            // int              nx = x & (hpow - 1), ny = y & (hpow - 1);
            // int              nrot          = (rot + rotateDelta[seg]) & 3;
            // ll               subSquareSize = 1LL << (2 * pow - 2);
            // ll               ans           = seg * subSquareSize;
            // ll               add           = hilbertOrder(nx, ny, pow - 1, nrot);
            // ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
            // return ans;
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

        for (const auto& qr : queries)
        {
            int l = qr.l;
            int r = qr.r;

            while (R < r)
            {
                ++R;
                res += freq[op(pref[R], k)];
                freq[pref[R]]++;
            }
            while (R > r)
            {
                freq[pref[R]]--;
                res -= freq[op(pref[R], k)];
                --R;
            }
            while (L < l)
            {
                freq[pref[L]]--;
                res -= freq[op(pref[L], k)];
                ++L;
            }
            while (L > l)
            {
                --L;
                res += freq[op(pref[L], k)];
                freq[pref[L]]++;
            }

            ans[qr.idx] = res;
        }

        for (ll x : ans)
            cout << x << '\n';
    }
};
