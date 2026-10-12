struct STab2d
{
    int                                lgn = 0, lgm = 0;
    vector<vector<vector<vector<ll>>>> dp;

    ll op(ll a, ll b)
    {
        return min(a, b);
    }
    STab2d(const vvi& a)
    {
        int n = a.size();
        int m = a[0].size();
        lgn   = __lg(n) + 1;
        lgm   = __lg(m) + 1;
        dp.assign(lgn, vector<vector<vector<ll>>>(n, vector<vector<ll>>(lgm, vector<ll>(m))));
        for (int ir = 0; ir < n; ++ir)
        {
            for (int ic = 0; ic < m; ++ic)
                dp[0][ir][0][ic] = a[ir][ic];
            for (int jc = 1; jc < lgm; ++jc)
                for (int ic = 0; ic + (1 << jc) - 1 < m; ++ic)
                    dp[0][ir][jc][ic]
                        = op(dp[0][ir][jc - 1][ic], 
                             dp[0][ir][jc - 1][ic + (1 << (jc - 1))]);
        }
        for (int jr = 1; jr < lgn; ++jr)
            for (int ir = 0; ir + (1 << jr) - 1 < n; ++ir)
                for (int jc = 0; jc < lgm; ++jc)
                    for (int ic = 0; ic + (1 << jc) - 1 < m; ++ic)
                        dp[jr][ir][jc][ic]
                            = op(dp[jr - 1][ir][jc][ic], 
                                 dp[jr - 1][ir + (1 << (jr - 1))][jc][ic]);
    }
    // x2 >= x1, y2 >= y1
    int query(int x1, int x2, int y1, int y2)
    {
        int kn = __lg(x2 - x1 + 1);
        int km = __lg(y2 - y1 + 1);
        return min({ dp[kn][x1][km][y1],
                     dp[kn][x1][km][y2 - (1 << km) + 1],
                     dp[kn][x2 - (1 << kn) + 1][km][y1],
                     dp[kn][x2 - (1 << kn) + 1][km][y2 - (1 << km) + 1] });
    }
};
