// a data structure for query lca in O(log n), the lca of (u, v) is the minimum height of all nodes when traverse from u to v or v to u in euler path

/// TODO: Rewrite the SegmentTree using a custom op;
struct SegmentTree
{
    vector<int> st;
    vector<int> h, first, path;  // paths.reserve(2 * n), height.resize(n), vis.resize(n), first.resize(n)
    vector<vector<int>> a;
    int                 n;

    void euler(int u, int p, int depth = 0)
    {
        h[u]     = depth;
        first[u] = path.size();
        path.push_back(u);
        for (auto& v : a[u])
        {
            if (v == p)
                continue;
            euler(v, u, depth + 1);
            path.push_back(u);
        }
    }


    int op(int a, int b)
    {
        return (h[a] < h[b] ? a : b);
    }
    SegmentTree(vector<vector<int>>& a)
    : a(a)
    {
        int n1 = a.size();
        path.reserve(2 * n1);

        first.assign(n1, -1);
        h.assign(n1, 0);

        euler(1, 1);
        n = path.size();
        st.assign(2 * n, 0);

        std::copy(path.begin(), path.end(), st.begin() + n);
        for (int i = n - 1; i > 0; --i)
            st[i] = op(st[i << 1], st[i << 1 | 1]);

    }
    int query(int u, int v)
    {
        if (first[u] > first[v])
            swap(u, v);
        u = first[u];
        v = first[v];
        int lca = st[u + n];
        for (u += n, v += n + 1; u < v; u >>= 1, v >>= 1)
        {
            if (u & 1)
                lca = op(lca, st[u++]);
            if (v & 1)
                lca = op(lca, st[--v]);
        }
        return lca;
    }
};


