
ll f(ll x)
{
  // sometime we do not return when x = 0, just in case the problem not care about number 0 
    if (x <= 0)
        return 0;
    vvvi dp(2, vvi(20, vi(200)));

    vector<int> d;
    while (x)
    {
        d.push_back(x % 10);
        x /= 10;
    }
    reverse(d.begin(), d.end());
    int len     = d.size();
    int tot     = len * 9;
    dp[1][0][0] = 1;
    for (int i = 0; i < len; i++)
    {
        for (int sum = 0; sum <= tot; sum++)
        {
            for (int tight = 0; tight < 2; ++tight)
            {
                if (!dp[tight][i][sum])
                    continue;
                int lim = tight ? d[i] : 9;
                for (int digit = 0; digit <= lim; ++digit)
                {
                    int nxttight = (tight && digit == lim) ? 1 : 0;
                    dp[nxttight][i + 1][sum + digit] += dp[tight][i][sum];
                }
            }
        }
    }
    ll ans = 0;
    for (int tight = 0; tight < 2; ++tight)
    {
        for (int sum = 0; sum <= tot; ++sum)
        {
            ans += sum * dp[tight][len][sum];
        }
    }
    return ans;
}

ll g(ll l, ll r)
{
    return f(r) - f(l - 1);
}
