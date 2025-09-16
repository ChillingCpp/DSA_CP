void dfs(int u, int p = 0){

    dp[u][wt[u]] = val[u];
    for (int v : a[u])
    if (v != p){
        dfs(v, u);

        vi new_dp = dp[u];
        for (int i = 0; i <= W; ++i)
            for (int j = 0; j <= W - i; ++j)
                new_dp[i+j] = max(new_dp[i+j], dp[u][i] + dp[v][j]); // using i weight in dp[u] and j weight in dp[v]

        dp[u] = new_dp;
    }
}
