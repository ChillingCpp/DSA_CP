// a data structure for query lca in O(log n), the lca of (u, v) is the minimum height of all nodes when traverse from u to v or v to u in euler path
struct SegmentTree
{
    vector<int> st;
    vector<int> ht, first;
    int         n, maxh;

    SegmentTree(vector<int>& a, vector<int>& h)
    : st(2 * a.size())
    , n(a.size())    
    , first(h.size())
    , ht(h)
    , maxh(0)
    {
        std::copy(a.begin(), a.end(), st.begin() + n);
        for (int i = n - 1; i > 0; --i)
        {
            st[i] = (ht[st[i << 1]] < ht[st[i << 1 | 1]] ? st[i << 1] : st[i << 1 | 1]);
            maxh  = (ht[maxh] > ht[i] ? maxh : i);
        }
    }
    int query(int u, int v)
    {
        int lca = maxh;
        if (first[u] > first[v]) swap(u, v);
        for (u += n, v += n + 1; u < v; u >>= 1, v >>= 1)
        {
            if (u & 1)
                lca = (ht[u] < ht[lca] ? u++ : lca);
            if (v & 1)
                lca = (ht[--v] < ht[lca] ? v : lca);
        }
        return lca;
    }
};

vector<int>         path, height, vis, first;  // paths.reserve(2 * n), height.resize(n), vis.resize(n), first.resize(n)
vector<vector<int>> a;
void                euler(int u, int h = 0)
{
    vis[u]    = true;
    height[u] = h;
    first[u] = path.size();
    path.push_back(u);
    for (auto& v : a[u])
    {
        if (vis[v])
            continue;
        euler(v, h + 1);
        path.push_back(u);
    }
}
dfs(root); // dfs at the root of the tree
