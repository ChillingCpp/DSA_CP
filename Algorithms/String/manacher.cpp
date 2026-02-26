void manacher(string& s)
{
    int                 n = s.size();
    vector<vector<int>> p(2, vector<int>(n, 0));
    for (int z = 0; z < 2; z++)
    {
        int l = 0, r = 0;
        for (int i = 0; i < n; i++)
        {
            if (i < r)
                p[z][i] = min(r - i + !z, p[z][l + r - i + !z]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1])
                p[z][i]++, L--, R++;
            if (R > r)
                l = L, r = R;
        }
    }
}
ll countP(vector<vector<int>> &p)
{
    ll ans =0;
    for (int i =0; i < n; ++i)
        ans += p[0][i] + p[1][0];
    return ans;
}
int getmx(vector<vector<int>> &p)
{
    int ans = 0;
    for (int i =0 ; i < n; ++i)
        ans = max({ans, 2 * p[0][i], 2 *p[1][i] + 1});
    return ans;
}
vector<int> LPend(vector<vector<int>> &p)
{
    vector<int> ans(n);
    for (int i = 0; i < n; ++i)
    {
        int l0 = i - p[0][i], r0 = i + p[0][i]-1;
        int l1 = i - p[1][i], r1 = i + p[1][i];
        if (r0 >= l0) ans[r0] = max(ans[r0], r0 - l0 + 1);
        ans[r1] = max(ans[r1], r1 - l1 + 1);
    }
    for (int i = n-1; i >= 0; --i)    
        ans[i] = max(ans[i], ans[i+1] -2);
    cout << ans << '\n';
}
bool query(int l, int r, vector<vector<int>>& p)
{
    int len = r - l + 1;
    int z = len & 1;
    int mid = (l + r + !z) /2;
    return p[z][mid] >= len/2;
}
