int  n, m;
vvi  a;
vi   in;
void input()
{
    cin >> n >> m;
    a.resize(n + 1);
    in.resize(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        in[v]++;
    }
}
void solve()
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; ++i)
        if (in[i] == 0)
            pq.push(i);
    vector<int> ans;
    while (pq.size())
    {
        int u = pq.top();
        pq.pop();
        ans.push_back(u);
        for (auto v : a[u])
        {
            in[v]--;
            if (in[v] == 0)
                pq.push(v);
        }
    }
    if (ans.size() != n)
        cout << "Sandro fails.";
    else
        cout << ans << '\n';
}
