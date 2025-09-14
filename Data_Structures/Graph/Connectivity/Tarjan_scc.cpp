struct Tarjan
{
    vvi         a, sccs;
    vector<int> low, disc, st;
    stack<ll>   s;

    int  t = 0;
    void dfs(int u)
    {
        low[u] = disc[u] = ++t;
        st[u]            = true;
        s.push(u);

        for (auto& v : a[u])
        {
            if (!disc[v])
            {
                dfs(v);
                /// low[u] = min(low[u], low[v]) khi v chưa được khám phá là do ta có đường đi từ u
                /// -> v, mà ta lại biết v có thể quay về 1 tổ tiên có disc nhỏ nhất ( gọi là z ),
                /// vậy nên u cũng có thể quay về tổ tiên z đó ( theo u -> v -> z )
                low[u] = min(low[u], low[v]);
            }
            else if (st[v])
                /// low[u] = min(low[u], disc[v]) khi v đã khám phá là do v là tổ tiên của u, xét
                /// hiện tại thì ta chỉ biết u có thể quay về v ta sẽ không tính low[u] =
                /// min(low[u], low[v]) vì low[u] sẽ chỉ tính các back edge quay ngược trực tiếp chứ
                /// không phải qua 2 lần chạy back edge hoặc nhiều hơn từ u -> v -> z, với z là đỉnh
                /// có disc[z] = low[v], v có back edge khác ta sẽ không xét
                low[u] = min(low[u], disc[v]);
        }

        if (low[u] == disc[u])
        {
            vi scc;
            while (true)
            {
                int v = s.top();
                st[v] = false;
                scc.push_back(v);
                if (v == u)
                    break;
            }
            sccs.push_back(scc);
        }
    }

    void process()
    {
        for (int i = 1; i <= n; ++i)
            if (!disc[i])
                dfs(i);
    }
};
