struct Node
{
    int low = 0, disc = 0, ap = 0;
};
struct Bridge
{
    int u = 0, v = 0;
};
vvi            a, sccs;
vector<Node>   node;
vector<Bridge> bridge;

int  t = 0;
void tarjan(int u, int p)
{
    node[u].low = node[u].disc = ++t;

    int child = 0;

    for (int v : a[u])
    {
        if (v == p)
            continue;

        if (!node[v].disc)
        {
            child++;
            tarjan(v, u);
            /// if the v is in the component of u or v is discovery earlier than u then u is the
            /// articular point
            if (node[u].disc <= node[v].low)
                node[u].ap = 1;
            // if (disc[v] == low[u]) then we have encounterd a cycle, if we disconnected the edge
            // {u, v} then nothing will happened
            if (node[u].disc < node[v].low)  //
                bridge.push_back({ u, v });

            node[u].low = min(node[u].low, node[v].low);
        }
        else
            node[u].low = min(node[u].low, node[v].disc);
    }
    if (child > 1)
        node[u].ap = 1;
}
// main code //
for (int i = 1; i <= n; ++i)
    if (!node[i].disc)
        tarjan(i);
