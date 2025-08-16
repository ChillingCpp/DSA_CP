
/// Mo algorithm

struct Motree
{
    vector<int> euler, ST, EN, h, vis;
    vvi&        a;
    int         n;
    Motree(vvi& tree)
    : a(tree)
    , n(tree.size())
    {
        euler.reserve(2 * n);
        ST.assign(n, -1);
        EN.assign(n, -1);
        h.assign(n, -1);
        vis.assign(n, 0);
        dfs(1);  // or 0 if 0 based
        for (int i = 0; i < euler.size(); ++i)
        {
            if (ST[euler[i]] == -1) ST[euler[i]] = i;
            else EN[euler[i]] = i;
        }
    }
    void dfs(int u, int depth = 0)
    {
        vis[u] = true;
        h[u]   = depth;
        euler.push_back(u);
        for (auto v : a[u])
        {
            if (vis[v])
                continue;

            dfs(v, depth + 1);
            euler.push_back(u);
        }
    }
};