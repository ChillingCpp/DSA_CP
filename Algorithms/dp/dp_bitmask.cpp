int tsp(vector<vector<int>>& dist)
{
    // Code here
    int                 n   = dist.size();
    int                 inf = 1e9;
    vector<vector<int>> dp(1 << n, vector<int>(n, inf));

    dp[1][0] = 0;
    for (int mask = 0; mask < (1 << n); ++mask)
    {
        for (int i = 0; i < n; ++i)
        {
            if (!(mask & (1 << i)))
                continue;  //  check i is in setbit
            for (int j = 0; j < n; ++j)
            {
                if (mask & (1 << j))
                    continue;  // transition from i to j require j not in the mask. but in some
                               // problem j can be revisited and rewrite the state, but in this case
                               // j not allowed to be revisited.
                int newmask    = mask | (1 << j);
                dp[newmask][j] = min(dp[newmask][j], dp[mask][i] + dist[i][j]);
            }
        }
    }
    int ans = inf;
    for (int i = 0; i < n; ++i)
        ans = min(ans, dp[(1 << n) - 1][i] + dist[i][0]);

    return ans;
}

/// bài toán : tìm 2 tập con S và T trong mảng A sao cho S khác T và sum(S) + sum(T) là max
int masSum()
{
    // Precompute sum for every mask
    vector<int> sum(1 << n, 0);
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum[mask] += A[i];
            }
        }
    }

    int best = -1e9;
    // Duyệt mọi mask
    for (int mask = 0; mask < (1 << n); mask++) {
        // Duyệt mọi submask của mask
        for (int submask = mask; submask; submask = (submask - 1) & mask) {
            // submask là tập S
            // mask ^ submask là tập T
            int S = submask;
            int T = mask ^ submask; // phần còn lại trong mask

            int total = sum[S] + sum[T];
            if (total > best) {
                best = total;
            }
        }
    }
    return best;
}
