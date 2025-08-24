
// tarjan algorithms for scc
struct Node
{
    int  low = 0, disc = 0;
    bool st = false;
};
vvi          a, sccs;
vector<Node> node;
stack<ll>    s;

int  t = 0;
void tarjan(int u)
{
    node[u].low = node[u].disc = ++t;
    s.push(u);
    node[u].st = true;

    for (auto& v : a[u])
    {
        if (!node[v].disc)
        {
            tarjan(v);
            node[u].low = min(node[u].low, node[v].low);
        }
        else if (node[v].st)
            node[u].low = min(node[u].low, node[v].disc);
    }

    if (node[u].low == node[u].disc)
    {
        vi scc;
        while (true)
        {
            int v = s.top();
            s.pop();
            node[v].st = false;
            scc.push_back(v);
            if (v == u)
                break;
        }
        sccs.push_back(scc);
    }
}
// main code //
for (int i = 1; i <= n; ++i)
    if (!node[i].disc)
        tarjan(i);

