
#include "../seg_tree/seg_tree.cpp"

struct HLD
{
    int          n, t = 0;
    vi           sz, head, in, out, pr, d;
    vector<Node> eval, nval;
    vvpii        a;

    void dfs(int u, int p, int dd = 0, ll ww = 0)
    {
        d[u]    = dd;
        eval[u] = ww;
        sz[u]   = 1;
        pr[u]   = p;
        for (auto& v : a[u])
            if (v.first != p)
            {
                dfs(v.first, u, dd + 1, v.second);
                sz[u] += sz[v.first];
                if (a[u][0].first == p || (sz[v.first] > sz[a[u][0].first]))
                    swap(v, a[u][0]);
            }
    }
    void hld(int u, int p)
    {
        in[u] = ++t;
        for (auto [v, w] : a[u])
            if (v != p)
            {
                head[v] = (v == a[u][0].first ? head[u] : v);
                hld(v, u);
            }
        out[u] = t;
    }
    Node query(int u, int v, Seg& edge, Seg& node)
    {
        Node res = -1e18;
        for (; head[u] != head[v]; v = pr[head[v]])
        {
            if (d[head[u]] > d[head[v]])
                swap(u, v);
            res = combine(res, edge.query(in[head[v]], in[v]));
            res = combine(res, node.query(in[head[v]], in[v]));
        }
        if (d[u] > d[v])
            swap(u, v);
        res = combine(res, edge.query(in[u] + 1, in[v]));
        res = combine(res, node.query(in[u], in[v]));
        return res;
    }
    void solve()
    {
        head[1] = 1;  // quan trọng
        dfs(1, 0);
        hld(1, 0);
        vector<Node> f(n + 1), f2(n + 1);
        for (int i = 1; i <= n; ++i)
            f[in[i]] = eval[i], f2[in[i]] = nval[i];
        Seg edge(f);
        Seg node(f2);
        while (true)
        {
            int tp, i, c;
            cin >> tp >> i >> c;
            if (tp == 1)
            {
                auto [u, v, w] = e[i - 1];
                if (u != pr[v])
                    swap(u, v);
                edge.modify(in[v], c);
            }
            else if (tp == 2)
            {
                node.modify(in[i], c);
            }
            else
                cout << query(i, c, edge, node) << '\n';
        }
    }
};
