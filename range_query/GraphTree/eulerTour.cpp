vector<int>         euler, st, en;  // paths.reserve(2 * n);
vector<vector<int>> a;
int timer = 0; // if 1 based

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
