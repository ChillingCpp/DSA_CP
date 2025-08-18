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
