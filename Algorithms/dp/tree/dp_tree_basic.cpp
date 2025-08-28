
vector<int> sz; 
vector<vector<int>> a;

void dfs(int u, int p)
{
    sz[u] = 1;
    for (int v : a[u])
    {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v]; /// include node v to u
    }
}
