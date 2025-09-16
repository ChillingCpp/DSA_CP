/// You are given a rooted tree where each node has a weight and a profit. You want to select a subset of nodes such that:
/// The parent of a selected node must also be selected. /// this is when we can optimization
/// The total weight does not exceed W.
/// The goal is to maximize total profit.

vi p, wt, pr; // 1 based index // weight at u and profit at u
vvi a, kn; // dp and graph, assign kn all by -1, kn[o][0] = 0, result is max(kn[0][i]) for all 1 <= i <= W
ll n, W; // total cost

void dfs1(int u, int pp = 0)
{
    p[u] = pp;
    for (auto v : a[u]) if (v != pp) dfs1(v, u);
}
void dfs2(int u)
{
    // first copying kn[p[u]] to kn[u]
    for (int i = 0; i<= W; ++ i){
        kn[u][i] = kn[p[u]][i];
    }
    for (auto v : a[u])
        if (v != p[u]) dfs2(v);

    for (int i = 0; i + wt[u] <= W; ++i){
        if (kn[u][i] != -1){
            kn[p[u]][i+ wt[u]] = max(kn[p[u]][i], pr[u] + kn[u][i]);
        }
    }
}
