struct DP
{
    ll nodeVal;
    ll edgeVal;
};

const int MAXN = 200005;
const int LOG  = 20;

int         n;
vector<pii> adj[MAXN];
int depth[MAXN];
int up[MAXN][LOG];
ll  nodeValue[MAXN];
DP dp[MAXN][LOG];

ll opNode(ll a, ll b)
{
    return a + b;  // đổi nếu cần
}
ll opEdge(ll a, ll b)
{
    return a + b;  // đổi nếu cần
}
DP combine(DP a, DP b)
{
    DP res;
    res.nodeVal = opNode(a.nodeVal, b.nodeVal);
    res.edgeVal = opEdge(a.edgeVal, b.edgeVal);
    return res;
}
void dfs(int u, int p = 0, ll w_to_p = 0)
{
    up[u][0] = p;
    dp[u][0].nodeVal = nodeValue[u];
    dp[u][0].edgeVal = w_to_p;
    for (int k = 1; k < LOG; k++)
    {
        up[u][k] = up[up[u][k - 1]][k - 1];
        dp[u][k] = combine(dp[u][k - 1], dp[up[u][k - 1]][k - 1]);
    }
    for (auto [v, w] : adj[u])
        if (v != p)
        {
            depth[v] = depth[u] + 1;
            dfs(v, u, w);
        }
}
pair<int, DP> queryPath(int u, int v)
{
    DP ans = { 0, 0 };
    if (depth[u] < depth[v])
        swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; (1 << i) <= diff; ++i)
        if (diff & (1 << i))
            ans = combine(ans, dp[u][i]), u = up[u][i];
    if (u == v)
    {
        ans.nodeVal = opNode(ans.nodeVal, nodeValue[u]);  // thêm node lca
        return { u, ans };
    }
    for (int k = LOG - 1; k >= 0; k--)
        if (up[u][k] != up[v][k])
            ans = combine(ans, combine(dp[u][k], dp[v][k])), u = up[u][k], v = up[v][k];
    ans         = combine(ans, combine(dp[u][0], dp[v][0]));
    ans.nodeVal = opNode(ans.nodeVal, nodeValue[up[u][0]]);
    return { up[u][0], ans };
}

