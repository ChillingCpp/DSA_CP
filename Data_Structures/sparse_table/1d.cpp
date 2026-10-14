struct STab
{
    int lg;
    vvi dp;  // dp[j][i] : op of [i...i + 2^j - 1];
    // dp[j][i] = op(dp[j-1][i], dp[j-1][i + (1 << (j-1))]);
    // vi lg2; :  lg2[i] = lg2[i/2]+1; : tính nhanh lg nếu quên hàm __lg()
    /// sparse table based on sliding window technique
    /// we can use sparse table similar to solve some sliding window technique.

    ll op(ll a, ll b)
    {
        return min(a, b);
    }
    STab() = default;
    STab(const vi& a)
    : lg(__lg(a.size()) + 1)
    {
        int n = a.size();
        lg    = __lg(n) + 1;
        dp.assign(lg, vi(n));
        copy(a.begin(), a.end(), dp[0].begin());
        for (int j = 1; j < lg; ++j)
            for (int i = 0; i + (1 << j) - 1 < n; ++i)
                dp[j][i] = op(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
    }
    // idempotent
    int query(int l, int r)
    {
        int k = __lg(r - l + 1);  // k = lg2[r-l+1];
        return op(dp[k][l], dp[k][r - (1 << k) + 1]);
    }
};
