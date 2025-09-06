template<int MAXN>
struct MaxFlow
{
    typedef ll Flow;

    struct Edge
    {
        int  to;         // Đỉnh đích
        int  reverseid;  // Chỉ số của cạnh ngược trong danh sách kề của đỉnh 'to'
        Flow capacity;   // Dung lượng còn lại (residual capacity)
    };
    const Flow INF = numeric_limits<Flow>::max();

    int n, source, sink;

    vector<Edge> adj[MAXN];

    vector<int> activeList[MAXN], gapList[MAXN];
    Flow excess[MAXN];
    int h[MAXN], cntH[MAXN], highest, work;

    void addEdge(int u, int v, Flow capacity)
    {
        Edge a{v, (int) adj[v].size(), capacity}, b{ u, (int) adj[u].size(), 0 };
        adj[u].push_back(a), adj[v].push_back(b);
    }
    void updateHeight(int v, int newHeight)
    {
        work++;
        // Giảm bộ đếm ở chiều cao cũ (nếu chưa bị xóa)
        if (h[v] < n)  cntH[h[v]]--;
        h[v] = newHeight;

        if (newHeight >= n)  return;  // đánh dấu không thể đến đích

        cntH[newHeight]++;
        highest = max(highest, newHeight);
        gapList[newHeight].push_back(v);

        // Nếu đỉnh này có luồng dư, thêm vào danh sách xử lý
        if (excess[v] > 0) activeList[newHeight].push_back(v);
    }

    /// globalrelabel gồm có 2 nhiệm vụ chính :
    /// reset lại các biến, không bao gồm excess flow
    /// bfs ngược từ sink tới source
    void globalRelabel()
    {
        /// reset lại toàn bộ các đỉnh cân xử lí
        work = 0;
        for (int i = 0; i < n; i++)
        {
            h[i]    = n; 
            cntH[i] = 0;
        }
        for (int i = 0; i <= highest; i++)
        {
            activeList[i].clear();
            gapList[i].clear();
        }

        // BFS từ đích (t) trên đồ thị dư (theo chiều ngược lại)
        queue<int> q;
        q.push(sink);
        h[sink] = 0;
      
        while (q.size())
        {
            int u = q.front();
            q.pop();
            highest = h[u];  // cập nhật chiều cao cao nhất trong BFS

            for (const Edge& e : adj[u])
            {
                // nếu e.to chưa được cập nhật và có cạnh ngược của e.to tới u
                if (h[e.to] == n && adj[e.to][e.reverseid].capacity > 0)
                {
                    h[e.to] = h[u] + 1;
                    q.push(e.to);
                    updateHeight(e.to, h[u] + 1); 
                }
            }
        }
    }

    // Đẩy luồng từ đỉnh u sang đỉnh v
    void push(int u, Edge& e)
    {
        int  v    = e.to;
        Flow flow = min(excess[u], e.capacity);

        // Nếu v đang không có dư, sau khi nhận sẽ có → thêm vào hàng đợi
        if (excess[v] == 0) activeList[h[v]].push_back(v);

        e.capacity -= flow, adj[v][e.reverseid].capacity += flow;
        excess[u] -= flow, excess[v] += flow;
    }
    void discharge(int u)
    {
        int minH = n; 
        for (Edge& e : adj[u])
        {
            if (e.capacity > 0)
            {
                if (h[u] == h[e.to] + 1)
                {
                    push(u, e);
                    if (excess[u] <= 0) return;  
                }
                else
                    minH = min(minH, h[e.to] + 1);
            }
        }

        // Nếu còn nhiều hơn 1 đỉnh ở chiều cao hiện tại → relabel u
        if (cntH[h[u]] > 1)
            updateHeight(u, minH);
        else
        {
            /// không còn đỉnh nào ở h[u] ==> tất cả đỉnh >= h[u] không thể tới đích
            for (int height = h[u]; height <= highest; height++)
            {
                for (int w : gapList[height])
                    updateHeight(w, n);  // đánh dấu không thể tới đích
                gapList[h].clear();
            }
        }
    }

    // hàm chính
    Flow maxFlow(int N, int s, int t)
    {
        n      = N, source = s, sink   = t;

        if (source == sink) return -1; 

        fill(excess, excess + n, 0);
        excess[source] = INF;
        excess[sink]   = -INF;
        globalRelabel();

        for (Edge& e : adj[source])
            if (e.capacity > 0) push(source, e);

        for (highest = n - 1; highest >= 0; highest--)
        {
            while (activeList[highest].size())
            {
                int u = activeList[highest].back();
                activeList[highest].pop_back();

                if (excess[u] > 0)  discharge(u);

                if (work > 4 * n) globalRelabel();
            }
        }
        return excess[sink] + INF;
    }
};



/// maxflow có 4 hàm chính :
/// globalRelabel();
/// push();
/// discharge();
/// updateHeight()