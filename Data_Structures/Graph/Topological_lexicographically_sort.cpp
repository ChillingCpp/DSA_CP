int main()
{
    fastio;
    int n, m;
    cin >> n >> m;
    vvi ra(n + 1);
    vi  out(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        ra[b].push_back(a);
        out[a]++;
    }

    // we do this in reverse so min heap -> max heap
    priority_queue<int> pq;
    for (int i = 1; i <= n; ++i)
    {
        if (!out[i])
            pq.push(i);
    }
    vector<int> ans;
    while (pq.size())
    {
        int x = pq.top();
        pq.pop();
        ans.push_back(x);
        for (auto& v : ra[x])
        {
            out[v]--;
            if (!out[v])
                pq.push(v);
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans << '\n';
}
