

/// compute something relative with vertices degree
struct Sqrtheavylight
{
    vvi a;
    vector<bool> is_heavy;
    vector<int> heavy;
    int block;


    // additional variable : DSU internal implementation...

    /// applications : 
    /// Dynamic Connectivity : can be solved using DSU with Rollbacks
    /// Dynamic Triangle Counting 
    /// Dynamic k-Core
    /// Dynamic Shortest Paths
    /// Dynamic Bipartiteness 

    /// very rare in CP ;
    /// Dynamic Graph Coloring
    /// Dynamic Maximum Matching
    /// Dynamic Clustering Coefficient 
    /// Dynamic Vertex Cover

    Sqrtheavylight(int n) : block(sqrt(n) + 1){
        
        a.resize(n);
        is_heavy.resize(n);
        heavy.resize(n);
    }
    void add(int u, int v)
    {
        a[u].push_back(v);
        a[v].push_back(u);

        if (a[u].size() == block)
        {
            is_heavy[u] = 1;
            heavy.push_back(u);
        }
        if (a[v].size() == block)
        {
            is_heavy[v] = 1;
            heavy.push_back(v);
        }
    }

};  