const ll INF = 5e18;

struct DistSrc
{
    ll   dist;
    int  src;
    bool operator>(const DistSrc& other) const
    {
        return dist > other.dist;
    }
    bool operator<(const DistSrc& other) const
    {
        return dist < other.dist;
    }
};

struct Query
{
    ll a, b;
};

struct GraphEdge
{
    int to;
    ll  weight;
};

struct DijkstraItem
{
    ll   dist;
    int  node;
    int  src;
    bool operator>(const DijkstraItem& other) const
    {
        return dist > other.dist;
    }
};

// === Quản lý nhãn tại mỗi đỉnh ===
struct Owner
{
    array<DistSrc, 2> data;  // Hai nhãn tốt nhất: {dist, src}

    Owner()
    {
        data = { { { INF, -1 }, { INF, -1 } } };
    }

    // Truy cập trực tiếp
    DistSrc& operator[](int i)
    {
        return data[i];
    }
    const DistSrc& operator[](int i) const
    {
        return data[i];
    }

    // Thêm nhãn mới, giữ lại 2 tốt nhất
    bool insert(ll d, int s)
    {
        // Nếu đã tồn tại src, cập nhật nếu tốt hơn
        for (int i = 0; i < 2; ++i)
        {
            if (data[i].src == s)
            {
                if (d < data[i].dist)
                {
                    data[i].dist = d;
                    // Sắp xếp để data[0] <= data[1]
                    if (data[1] < data[0])
                        swap(data[0], data[1]);
                }
                return d < data[i].dist;
            }
        }

        // Chưa tồn tại: chèn nếu tốt hơn một trong hai
        if (d < data[1].dist)
        {
            data[1] = { d, s };
            if (data[1] < data[0])
                swap(data[0], data[1]);
            return true;
        }
        return false;
    }

    // Lấy danh sách nhãn khác src
    vector<DistSrc> others(int src) const
    {
        vector<DistSrc> res;
        for (const auto& ds : data)
        {
            if (ds.src != -1 && ds.src != src)
            {
                res.push_back(ds);
            }
        }
        return res;
    }
};


void solve()
{
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<vector<GraphEdge>> a(N + 1);
    for (int i = 0; i < M; ++i)
    {
        int x, y, t;
        cin >> x >> y >> t;
        a[x].push_back({ y, t });
        a[y].push_back({ x, t });
    }
    vector<Query> queries(Q);


    // Đọc truy vấn
    for (int i = 0; i < Q; ++i)
    {
        ll a, b;
        cin >> a >> b;
        queries[i] = { a, b };
    }


    vector<int> node2src(N + 1, -1);
    int         nextSrcId = 0;
    for (const auto& q : queries)
    {
        int u = q.a;
        int v = q.b;
        if (node2src[u] == -1)
            node2src[u] = nextSrcId++;
        if (node2src[v] == -1)  // nếu đồ thị có hướng từ u -> v thì sẽ không xét v là source.
            node2src[v] = nextSrcId++;
    }

    // Map: cặp (src1, src2) -> danh sách chỉ số truy vấn
    auto makeKey = [](int a, int b) -> ll
    {
        if (a > b)
            swap(a, b);
        return (1ll << 32) * a + b;  // Giả sử src < 1e6
    };
    unordered_map<ll, vector<int>> queryMap;
    vector<ll>                     ans(M, INF);

    for (int i = 0; i < Q; ++i)
    {
        int sa = node2src[queries[i].a];
        int sb = node2src[queries[i].b];
        if (sa == sb)
            ans[i] = 0;
        else
            queryMap[makeKey(sa, sb)].push_back(i);
    }

    // Khởi tạo Dijkstra
    vector<Owner>                                                 owners(N + 1);
    priority_queue<DijkstraItem, vector<DijkstraItem>, greater<>> pq;

    // Đẩy các nguồn vào hàng đợi
    for (int u = 1; u <= N; ++u)
    {
        if (node2src[u] != -1)
            pq.push({ 0, u, node2src[u] });
    }

    // Hàm cập nhật truy vấn
    auto updateAnswer = [&](int src1, int src2, ll dist)
    {
        if (src1 == src2)
            return;
        ll   key = makeKey(src1, src2);
        auto it  = queryMap.find(key);
        if (it == queryMap.end())
            return;

        for (int idx : it->second)
            if (dist < ans[idx])
                ans[idx] = dist;

        queryMap.erase(it);  // Không cần xử lý lại
    };


    while (!pq.empty() && !queryMap.empty())
    {
        auto [d, u, src] = pq.top();
        pq.pop();

        // Kiểm tra nhãn lỗi thời
        bool outdated = true;
        for (int i = 0; i < 2; ++i)
        {
            if (owners[u][i].src == src && owners[u][i].dist <= d)
            {
                outdated = false;
                break;
            }
        }
        if (outdated)
            continue;

        // các source khác nhau gặp nhau tại đỉnh u
        for (const auto& other : owners[u].others(src))
            updateAnswer(src, other.src, d + other.dist);

        // Cập nhật nhãn tại u
        if (!owners[u].insert(d, src))
            continue;

        // Lan truyền đến các đỉnh kề
        for (const auto& edge : a[u])
        {
            int v  = edge.to;
            ll  nd = d + edge.weight;

            // các source khác nhau gặp nhau trên cạnh (tại v)
            for (const auto& other : owners[v].others(src))
                updateAnswer(src, other.src, nd + other.dist);

            pq.push({ nd, v, src });
        }
    }

    // In kết quả
    for (ll res : ans)
    {
        if (res == INF)
            cout << -1 << '\n';
        else
            cout << res << '\n';
    }
}

/// offline query + dijkstra
/// bài toán : cho N đỉnh, M cạnh vô hướng, Q truy vấn dạng s t, tìm đường đi ngắn nhất từ s -> t

/// thuật toán như sau : 

// distsrc : { dist, src }
// Item : { dist, node, src }, operator> compare dist min-heap
// Owner : hàm insert, array<distsrc, 2>
// insert : thay thế src nếu src tồn tại và d < data[i].d, return d < data[i].d
// nếu không thì thay data[1] và swap nếu data[1] < data[0]

// makekey function : hash 2 integer bằng shift a lên 32 bits, vì N, M <= 1e5
// update_answer : find key {src, dest} and update distance for all duplicated queries, after that remove the key.

// main loop :
/// kiểm tra nhãn hiện tại ( [d, u, src] ) bị cũ, nếu rồi thì bỏ qua
/// update ans tại các đỉnh source khác src đã từng tới  u
/// duyệt các cạnh kề u là v và update ans tại các đỉnh source khác src đã từng tới v.
/// push{nd, v, src};
/// in kết quả từng truy vấn 
