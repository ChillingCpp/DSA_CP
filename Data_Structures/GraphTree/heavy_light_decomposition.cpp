#include "../seg_tree/seg_tree.cpp"

struct HLD
{
    struct Edge
    {    
        int u, v, w;
    };
    int          n, q, t = 0;
    vi           sz, head, in, out, pr, d;
    vector<Node> eval, nval;
    vvpii        a;
    vector<Edge> e;

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
        res = combine(res, edge.query(in[u] + 1, in[v])); // not include lca
        res = combine(res, node.query(in[u], in[v]));
        return res;
    }
    void solve()
    {

        cin >> n >> q;
        val.resize(n + 1);
        sz.resize(n + 1);
        in.resize(n + 1);
        head.resize(n + 1);
        d.resize(n + 1);
        out.resize(n + 1);
        pr.resize(n + 1);
        a.resize(n + 1);
        
        for (int i = 0; i < n - 1; ++i)
        {
            int x, y, w;
            cin >> x >> y >> w;
            a[x].push_back({ y, w });
            a[y].push_back({ x, w });
            e.push_back({ x, y, w });
        }
        head[1] = 1;  // quan trọng
        dfs(1, 0);
        hld(1, 0);
        vector<Node> f(n + 1), f2(n + 1);
        for (int i = 1; i <= n; ++i)
            f[in[i]] = eval[i], f2[in[i]] = nval[i];
        Seg edge(f);
        Seg node(f2);
        for (int  i= 0; i < q; ++i)
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
