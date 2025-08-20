/// Mo algorithm, using sqrt decomposition on euler tour and Mo query
struct Motree
{
    struct Query
    {
        int l, r, idx, ord, lca;
        Query() = default;
        Query(int l, int r, int i, int lca)
        : l(l)
        , r(r)
        , idx(i)
        , lca(lca)
        {
            ord = hilbert_order(l, r, 21);
        }
        inline ll hilbert_order(int x, int y, int pow)
        {
            ////// ..... /////// see hilbert_order.cpp for more information
        }
        bool operator<(const Query& b)
        {
            return ord < b.ord;
        }
    };

    /// basic need for Mo on tree
    vector<int> euler;
    vector<int> st, en, depth;  // binlift for Mo algorithm need st and en array
    int         n, lg, timer;

    /// we can using the up table to store more information, generalize its into a struct contain
    /// more information about the 2^i ancestor, and information about path from 2^i ancestor to u
    vector<vector<int>> a, up;


    Motree()
    : timer(0)
    {
    }

    // check if u is ancestor of v
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


    //// important !!!
    void dfs(int u, int p)
    {
        st[u]        = ++timer;
        euler[timer] = u;
        up[u][0]     = p;
        for (int i = 1; i < lg; ++i)
            up[u][i] = up[up[u][i - 1]][i - 1];

        for (int v : a[u])
        {
            if (v == p)
                continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }

        en[u]        = ++timer;
        euler[timer] = u;
    }



    vector<int> val, freq, ans, vis;
    int         res = 0;

    // solving example problem : COT2 on spoj
    void add(int node)
    {
        freq[val[node]]++;
        if (freq[val[node]] == 1)
            res++;
    }
    void remove(int node)
    {
        if (!freq[val[node]])
            return;
        freq[val[node]]--;
        if (freq[val[node]] == 0)
            res--;
    }


    /// if a node been visited 2 time then it must be removed ( because its not in the path from u -> v ), the different between Mo normal and Mo on tree
    void check(int node)
    {
        if (vis[node])
            remove(node);
        else
            add(node);
        vis[node] ^= 1;
    }
    void solve(int root = 1)
    {
        int n, q;
        cin >> n >> q;

        lg = __lg(n) + 1;
        val.resize(n + 1);
        vis.resize(n + 1);
        ans.resize(q);
        freq.resize(n + 1);
        a.resize(n + 1);
        st.resize(n + 1), en.resize(n + 1), depth.resize(n + 1);
        euler.resize(2 * n + 1);
        up.resize(n + 1, vector<int>(lg));
        up[root][0] = root;
        depth[root] = 0;

        for (int i = 1; i <= n; ++i)
            cin >> val[i];
        vector<int> d(val.begin() + 1, val.end());

        /// coordinate compression for frequency counting;
        sort(d.begin(), d.end());
        d.erase(unique(d.begin(), d.end()), d.end());
        for (int i = 1; i <= n; ++i)
            val[i] = lower_bound(d.begin(), d.end(), val[i]) - d.begin();

        for (int i = 0; i < n - 1; ++i)
        {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
        }
        dfs(root, root);  // if root is 1

        vector<Query> qr(q);
        for (int i = 0; i < q; ++i)
        {
            int u, v;
            cin >> u >> v;

            if (depth[u] > depth[v])
                swap(u, v);

            qr[i].lca = lca(u, v);
            if (qr[i].lca == u)
                qr[i].l = st[u], qr[i].r = st[v];
            else
                qr[i].l = en[u], qr[i].r = st[v];
            qr[i].idx = i;
        }
        sort(qr.begin(), qr.end());
        int L = qr[0].l, R = qr[0].l - 1;


        for (auto q : qr)
        {
            int l = q.l;
            int r = q.r;
            while (L < l)
                check(euler[L++]);
            while (R < r)
                check(euler[++R]);
            while (L > l)
                check(euler[--L]);
            while (R > r)
                check(euler[R--]);

            int u = euler[L], v = euler[R];
            if (q.lca != u && q.lca != v)
                check(q.lca);


            ans[q.idx] = res;
            if (q.lca != u && q.lca != v)
                check(q.lca);
        }
        for (int i = 0; i < q; ++i)
            cout << ans[i] << '\n';
    }
};



