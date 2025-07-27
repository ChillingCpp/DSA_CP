vector<bool>        vis;
vector<int>         paths;  // 2 * n
vector<vector<int>> a;

void dfs(int u, int& idx)
{
    vis[u]       = true;
    paths[++idx] = u;
    for (int& v : a[u])
    {
        if (vis[v])
            continue;
        dfs(v, idx);
        paths[++idx] = u;
    }
}
