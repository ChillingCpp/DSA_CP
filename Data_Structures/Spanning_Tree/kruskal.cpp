vector<tuple<int, int, int>> edges;
int                          n;  // number of edges
struct Dsu
{
    vector<int> parent;
    vector<int> size;
    Dsu(int n)
    : parent(n)
    , size(n, 1)
    {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x)
    {
        for (int x = parent[x]; x != parent[x]; x = parent[x])
        {
        }
        return x;
    }
    bool unite(int x, int y)
    {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry)
            return false;

        if (size[rx] > size[ry])
        {
            parent[ry] = rx;
            size[rx] += size[ry];
        }
        else
        {
            parent[rx] = ry;
            size[ry] += size[rx];
        }
        return true;
    }
};  
int kruskal()
{
    // tuple {w, u, v};
    sort(edges.begin(), edges.end());
    Dsu dsu(n);
    int min = 0;
    int cnt = 0;
    for (auto& e : edges)
    {
        int u = get<1>(e);
        int v = get<2>(e);
        int w = get<0>(e);
        if (dsu.unite(u, v))
        {
            min += w;
            cnt++;
        }
        if (cnt == n - 1)  // tree has n vertices and n - 1 edges and not forming a cycle
            break;
    }
    return min;
}
