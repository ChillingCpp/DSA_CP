struct Binlift
{
    /// we can using the up table to store more information, generalize its into a struct contain more information about the 2^i ancestor, and path to u
    vector<vector<int>> a, up; 
    vector<int>         st, en;
    int                 n, lg, timer;

    Binlift(vector<vector<int>>& adj, int root = 1)
    : a(adj)
    , n(a.size())
    , timer(0)
    {
        lg = __lg(n) + 1;
        st.resize(n), en.resize(n);

        up.resize(n, vector<int>(lg));
        up[root][0] = root;
        dfs(root, root);  // if root is 1
    }
    bool is_ances(int u, int v)
    {
        return st[u] <= st[v] && en[v] <= en[u];
    }
    int jump(int u, int k)
    {
        for (int i = 0; (1 << i) <= k; ++i)
        {
            if ((1 << i) & k)
                u = up[u][i];
        }
        return u;
    }

    void dfs(int u, int p)
    {
        st[u]    = ++timer;
        up[u][0] = p;
        for (int i = 1; i < lg; ++i)
            up[u][i] = up[up[u][i - 1]][i - 1];

        for (int v : a[u])
            if (v != p)
                dfs(v, u);

        en[u] = ++timer;
    }
    int lca(int u, int v)
    {
        if (is_ances(u, v))
            return u;
        if (is_ances(v, u))
            return v;

        for (int i = lg; i >= 0; --i)
            if (!is_ances(up[u][i], v))
                u = up[u][i];

        return up[u][0];
    }
};
