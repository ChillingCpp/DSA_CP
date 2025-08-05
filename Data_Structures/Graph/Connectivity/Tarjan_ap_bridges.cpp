
// tarjan algorithms for scc, bridges, articular points

vvi       a, sccs;
vi        low, disc, st, ap;  // assign all of them to 0
vpii      bridge;
stack<ll> s;

int  t = 0;
void tarjan(int u)
{
    low[u] = disc[u] = ++t;
    s.push(u);
    st[u]     = true;
    int child = 0;
    for (auto& v : a[u])
    {
        if (!disc[v])
        {
            child++;
            tarjan(v);
            /// if the v is in the component of u or v is discovery earlier than u then u is the
            /// articular point
            if (disc[v] <= low[u])
                ap[u] = 1;
            // if (disc[v] == low[u]) then we have encounterd a cycle, if we disconnected the edge
            // {u, v} then nothing will happened
            if (disc[v] < low[u])  //
                bridge.push_back({ u, v });


            low[u] = min(low[u], low[v]);
        }
        else if (st[v])
        {
            low[u] = min(low[u], disc[v]);
        }
    }
    if (child > 1)
        ap[u] = 1;
    if (low[u] == disc[u])
    {
        vi scc;
        while (true)
        {
            int v = s.top();
            s.pop();
            st[v] = false;
            scc.push_back(v);
            if (v == u)
                break;
        }
        sccs.push_back(scc);
    }
}
// main code //
for (int i = 1; i <= n; ++i)
    if (!disc[i])
        tarjan(i);
