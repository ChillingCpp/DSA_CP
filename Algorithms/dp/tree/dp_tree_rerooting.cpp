struct Rerooting
{
    vector<vector<int>> a;
    vector<ll>          dp, result;
    vector<int>         sz;  // size of subtree, may needed in some problems
    struct State{

    };
    Rerooting(vector<vector<int>>& a)
    : a(a)
    , dp(a.size())
    , result(a.size())
    , sz(a.size())
    {
    }

    void process(int u, int v){

    }
    State backup(int u){

    }
    void rollback(int u, State& s){

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
            process(u, v);
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


            rerooting(v, u);


            /// restore root
            exclude(v, u);
            include(u, v);
        }
    }
};
