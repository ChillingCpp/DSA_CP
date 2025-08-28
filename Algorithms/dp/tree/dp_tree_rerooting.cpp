struct Rerooting
{
    vector<vector<int>> a;
    vector<ll>          dp, result;
    vector<int>         sz;  // size of subtree, may needed in some problems

    Rerooting(vector<vector<int>>& a)
    : a(a)
    , dp(a.size())
    , result(a.size())
    , sz(a.size())
    {
    }
    // include / exclude subtree of v to u.

    void include(int u, int v)
    {
    }
    void exclude(int u, int v)
    {
    }
    void dfs(int u = 1, int p = 1)
    {
        /// initialize dp and some variables.

        /// dfs
        for (int v : a[u])
        {
            if (v == p)
                continue;
            dfs(v, u);
            include(u, v);
        }
    }
    void rerooting(int u, int p)
    {
        result[u] = dp[u];
        for (int v : a[u])
        {
            if (v == p)
                continue;

            /// change root u to node v
            exclude(u, v);
            include(v, u);


            dfs(v, u);


            /// restore root
            exclude(v, u);
            include(u, v);
        }
    }
};
