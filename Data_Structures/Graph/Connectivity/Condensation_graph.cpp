// we decompose a directed graph with cycles to a condensation graph
// A condensation graph is a Directed acyclic graph connect strongly connected componenents, which
// mean its a graph which Sccs are the vertices. condensation graph useful when we are dealing some
// representative value of a scc (mincost/maxcost travel) combine condensation graph with topo sort
// and dp to achive solution in O(N + M) ( topo sort is a dp technique )

// first get all sccs using tarjan algorithm then connect sccs together to build condensation graph


// tarjan algorithms for scc, bridges, articular points
struct CGraph
{
    vi        low, disc, st, comp;
    vvi       cgr, rcgr;  // condensation graph and its reverse
    stack<ll> s;
    int       t = 0, cmp = 1;

    void build(vvi& a)
    {
        int n = a.size() - 1;

        low.resize(n + 1);
        disc.resize(n + 1);
        st.resize(n + 1);
        comp.resize(n + 1);

        function<void(int)> dfs = [&](int u)
        {
            low[u] = disc[u] = ++t;
            s.push(u);
            st[u] = true;
            for (auto& v : a[u])
            {
                if (!disc[v])
                {
                    dfs(v);
                    low[u] = min(low[u], low[v]);
                }
                else if (st[v]) low[u] = min(low[u], disc[v]);
            }
            if (low[u] == disc[u])
            {
                while (s.size())
                {
                    int v = s.top();
                    s.pop();
                    st[v]   = false;
                    comp[v] = cmp;
                    if (v == u)  break;
                }
                cmp++;
            }
        };
        for (int i = 1; i <= n; ++i)
            if (!disc[i]) dfs(i);

        cgr.resize(cmp + 1);
        rcgr.resize(cmp + 1);

        vpii ed;
        for (int i = 1; i <= n; ++i)
            for (int v : a[i])
                if (comp[i] != comp[v]) ed.push_back({ comp[i], comp[v] });
        for (auto& e : ed)
        {
            rcgr[e.second].push_back(e.first);
            cgr[e.first].push_back(e.second);
        }
    }
};
