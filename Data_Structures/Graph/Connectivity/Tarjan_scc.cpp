
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
            /// low[u] = min(low[u], low[v]) khi v chưa được khám phá là do ta có đường đi từ u -> v, 
            /// mà ta lại biết v có thể quay về 1 tổ tiên có disc nhỏ nhất ( gọi là z ), 
            /// vậy nên u cũng có thể quay về tổ tiên z đó ( theo u -> v -> z )
            node[u].low = min(node[u].low, node[v].low);
        }
        else if (node[v].st)
            /// low[u] = min(low[u], disc[v]) khi v đã khám phá là do v là tổ tiên của u, xét hiện tại thì ta chỉ biết u có thể quay về v
            /// ta sẽ không tính low[u] = min(low[u], low[v]) vì low[u] sẽ chỉ tính các back edge quay ngược trực tiếp 
            /// chứ không phải qua 2 lần chạy back edge hoặc nhiều hơn từ u -> v -> z, với z là đỉnh có disc[z] = low[v], v có back edge khác ta sẽ không xét
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

