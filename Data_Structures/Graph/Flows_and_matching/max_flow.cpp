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

    int n;
    int source, sink;

    vector<Edge> adj[MAXN];
    // activeList[h]: danh sách các đỉnh có excess > 0 và height = h
    vector<int> activeList[MAXN];
    // gapList[h]: danh sách các đỉnh có height = h (dùng trong global relabel)
    vector<int> gapList[MAXN];
    // excess[v]: lượng luồng dư tại đỉnh v
    Flow excess[MAXN];
    // h[v]: chiều cao của đỉnh v
    int h[MAXN], cntH[MAXN];
    // maxActiveH: chiều cao cao nhất hiện tại có đỉnh dư
    int maxActiveH;
    // work: đếm số thao tác để kích hoạt global relabel định kỳ
    int work;

    void addEdge(int u, int v, Flow capacity)
    {
        adj[u].push_back({ v, (int) adj[v].size(), capacity });
        adj[v].push_back({ u, (int) adj[u].size(), 0 });
    }
    void updateHeight(int v, int newHeight)
    {
        work++;
        // Giảm bộ đếm ở chiều cao cũ (nếu chưa bị xóa)
        if (h[v] < n)
            cntH[h[v]]--;
        h[v] = newHeight;

        if (newHeight >= n)
            return;  // đánh dấu không thể đến đích

        cntH[newHeight]++;
        maxActiveH = max(maxActiveH, newHeight);
        gapList[newHeight].push_back(v);

        // Nếu đỉnh này có luồng dư, thêm vào danh sách xử lý
        if (excess[v] > 0)
            activeList[newHeight].push_back(v);
    }
    // Cập nhật lại tất cả chiều cao bằng BFS ngược từ đích (t)
    void globalRelabel()
    {
        work = 0;
        // Reset chiều cao và bộ đếm
        for (int i = 0; i < n; i++)
        {
            h[i]    = n;  // đánh dấu là "vô cực"
            cntH[i] = 0;
        }

        // Xóa các danh sách cũ
        for (int i = 0; i <= maxActiveH; i++)
        {
            activeList[i].clear();
            gapList[i].clear();
        }

        // BFS từ đích (t) trên đồ thị dư (theo chiều ngược lại)
        queue<int> q;
        q.push(sink);
        h[sink] = 0;
      
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            maxActiveH = h[u];  // cập nhật chiều cao cao nhất trong BFS

            for (const Edge& e : adj[u])
            {
                // Nếu cạnh ngược tồn tại (tức là có thể đi từ e.to đến u)
                // và đỉnh e.to chưa được thăm
                if (h[e.to] == n && adj[e.to][e.reverseid].capacity > 0)
                {
                    h[e.to] = h[u] + 1;
                    q.push(e.to);
                    updateHeight(e.to, h[u] + 1);  // gọi updateHeight để cập nhật các cấu trúc
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
        if (excess[v] == 0)
            activeList[h[v]].push_back(v);

        e.capacity -= flow;
        adj[v][e.reverseid].capacity += flow;
        excess[u] -= flow;
        excess[v] += flow;
    }

    // "Phóng thích" đỉnh u: đẩy hết luồng dư ra ngoài
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
                    if (excess[u] <= 0)
                        return;  // đã hết dư
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
            for (int height = h[u]; height <= maxActiveH; height++)
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
        /// Khởi tạo các giá trị, đặt base value
        n      = N;
        source = s;
        sink   = t;

        if (source == sink)
            return -1;  // trường hợp đặc biệt
      
        for (int i = 0; i < n; i++)
            excess[i] = 0;
        excess[source] = INF;
        excess[sink]   = -INF;
        globalRelabel();

        for (Edge& e : adj[source])
            if (e.capacity > 0)
                push(source, e);

        // Vòng lặp chính: xử lý các đỉnh có dư, ưu tiên chiều cao cao nhất
        for (maxActiveH = n - 1; maxActiveH >= 0; maxActiveH--)
        {
            while (!activeList[maxActiveH].empty())
            {
                int u = activeList[maxActiveH].back();
                activeList[maxActiveH].pop_back();

                if (excess[u] > 0)
                    discharge(u);
                // Định kỳ cập nhật lại nhãn để giữ hiệu suất
                if (work > 4 * n)
                    globalRelabel();
            }
        }
        // Luồng cực đại = lượng mà đích đã nhận thêm
        return excess[sink] + INF;
    }
};
