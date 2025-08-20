vector<int>         euler, st, en;  // paths.reserve(2 * n);
vector<vector<int>> a;
int timer = 0; // if 1 based

/// Mo algorithms or subtree queries
void dfs(int u, int p)
{
    st[u]        = ++timer;
    euler[timer] = u;
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


// for dynamic tree, support add/remove, online queries
vector<int>         paths;  // paths.reserve(2 * n);
vector<vector<int>> a;


void dfs(int u, int p)
{
    paths.push_back(u);
    for (int& v : a[u])

    {
        if (v == p)
            continue;
        dfs(v);
        paths.push_back(u);
    }
}
