vector<bool>        vis;
vector<int>         paths;  // paths.reserve(2 * n);
vector<vector<int>> a;

void dfs(int u)
{
    vis[u]       = true;
    paths.push_back(u);
    for (int& v : a[u])
    {
        if (vis[v])
            continue;
        dfs(v);
        paths.push_back(u);
    }
}
