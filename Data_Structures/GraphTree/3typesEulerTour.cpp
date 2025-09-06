// for dynamic tree, support add/remove, online queries, lca queries + segment tree, work with
// segment tree lazy propagation.
vector<int>         path, tin, tout;  // paths.reserve(2 * n - 1);, tin.resize(n), tout.resize(n);
vector<vector<int>> a;

void dfs(int u, int p)
{
    path.push_back(u);
    tin[u] = path.size() - 1;
    for (int& v : a[u])

    {
        if (v == p)
            continue;
        dfs(v, u);
        path.push_back(u);
    }
    tout[u] = path.size() - 1;
}

/// dp on tree euler, if dp direction is from the child to parent
/// then euler indexing is not working, this version from usaco, best for subtree queries because
/// [in[u], out[u]-1] is the subtree of u
vector<int>         tin, tout, order;  /// tin.resize(n), tout.resize(n), order.resize(n);
vector<vector<int>> a;
int                 timer = 0;
void                dfs(int u, int p)
{
    tin[u]        = timer++;
    order[tin[u]] = u;  // pre-order order
    for (int v : a[u])
    {
        if (v == p)
            continue;
        dfs(v, u);
    }
    tout[u] = timer;
}


vector<int>         euler, tin, tout;  // paths.reserve(2 * n);
vector<vector<int>> a;
int                 timer = 0;  // if 1 based

/// Mo algorithms ( not for dp on tree )
/// this version not support lca, need a binary lifting
void dfs(int u, int p)
{
    tin[u]       = ++timer;
    euler[timer] = u;
    for (int v : a[u])
    {
        if (v == p)
            continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }

    tout[u]      = ++timer;
    euler[timer] = u;
}
