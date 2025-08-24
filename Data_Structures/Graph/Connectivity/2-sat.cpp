struct Node
{
    int low = 0, disc = 0, st = 0, comp = 0;
};

int                 n, n1;
vector<vector<int>> a;
stack<int>          st;
vector<Node>        b;
int                 t  = 0;
int                 id = 1;


int Not(int u)
{
    return u + n;
}

void tarjan(int u)
{
    b[u].low = b[u].disc = ++t;
    b[u].st              = true;
    st.push(u);
    for (int v : a[u])
    {
        if (!b[v].disc)
        {
            tarjan(v);
            b[u].low = min(b[u].low, b[v].low);
        }
        else if (b[v].st)
            b[u].low = min(b[u].low, b[v].disc);
    }
    if (b[u].low == b[u].disc)
    {
        while (true)
        {
            int d   = st.top();
            b[d].comp = id;
            st.pop();
            if (d == u)
                break;
        }
        id++;
    }
}

n1 = 2 * n + 1;
a.resize(n1);
b.resize(n1);
for (int i = 0; i < m; ++i)
{
    int u, v;
    cin >> u >> v;
    a[Not(u)].push_back(v);
    a[Not(v)].push_back(u);
}
for (int i = 1; i <= 2 * n; ++i)  // 1 based index
    if (!b[i].disc)
        tarjan(i);

for (int i = 1; i <= n; ++i)
{
    if (b[i].comp == b[Not(i)].comp)
    {
        cout << "Impossible\n";
        return 0;
    }
}
