struct Binlift
{
    /// we can using the up table to store more information, generalize its into a struct contain more information about the 2^i ancestor, and path to u
    vector<vector<int>> a, up; 
    vector<int>         st, en, depth; // binlift for Mo algorithm need st and en array
    int                 n, lg, timer;

    Binlift(vector<vector<int>>& adj, int root = 1)
    : a(adj)
    , n(a.size())
    , timer(0)
    {
        lg = __lg(n) + 1;
        st.resize(n), en.resize(n), depth.resize(n);
    
        up.resize(n, vector<int>(lg));
        up[root][0] = root;
        depth[root] = 0;
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
    void dfs(int u, int p, int h = 0)
    {
        st[u]    = ++timer;
        
        up[u][0] = p;
        for (int i = 1; i < lg; ++i)
            up[u][i] = up[up[u][i - 1]][i - 1];

        for (int v : a[u]){
            if (v == p) continue;
            depth[v] = depth[u]+1;
            dfs(v, u, h + 1);
            
        }

        en[u] = ++timer;
    }
    int lca(int u, int v)
    {
        if (is_ances(u, v))
            return u;
        if (is_ances(v, u))
            return v;

        for (int i = lg - 1; i >= 0; --i)
            if (!is_ances(up[u][i], v))
                u = up[u][i];

        return up[u][0];
    }
};


