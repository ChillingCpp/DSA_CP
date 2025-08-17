/// for practical, use iterative instead

// range assignment, if addition then we change = to += 
struct SegmentTree
{

    vector<ll> tree, lazy;  // lazy[node] == LLONG_MIN nghĩa là không có lazy
    int        n;

    ll op1(ll a, ll b)
    {
        return a + b;
    }
    SegmentTree(const vector<ll>& arr)
    {
        n = arr.size();
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, LLONG_MIN);  // Khởi tạo tất cả là "không có lazy"
        build(1, 0, n - 1, arr);
    }

    // Gán đoạn [l, r] thành giá trị val
    void update(int l, int r, ll val)
    {
        update_range(1, 0, n - 1, l, r, val);
    }

    // Truy vấn tổng đoạn [l, r]
    ll query(int l, int r)
    {
        return query_range(1, 0, n - 1, l, r);
    }
    void build(int node, int start, int end, const vector<ll>& arr)
    {
        if (start == end)
            tree[node] = arr[start];
        else
        {
            int mid = (start + end) >> 1;
            build(node << 1, start, mid, arr);
            build(node << 1 | 1, mid + 1, end, arr);
            tree[node] = op1(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update_range(int node, int start, int end, int l, int r, ll val)
    {
        push(node, start, end);  // Đẩy lazy hiện tại ra

        if (start > r || end < l)
            return;

        if (start >= l && end <= r)
        {
            lazy[node] = val;
            push(node, start, end);  // cập nhật tree[node] ngay lập tức
            return;
        }

        int mid = (start + end) >> 1;
        update_range(node << 1, start, mid, l, r, val);
        update_range(node << 1 | 1, mid + 1, end, l, r, val);
        tree[node] = op1(tree[2 * node], tree[2 * node + 1]);
    }

    ll query_range(int node, int start, int end, int l, int r)
    {
        if (start > r || end < l)
            return 0;
        
        push(node, start, end);  // Luôn đảm bảo node sạch trước khi truy vấn

        if (start >= l && end <= r)
            return tree[node];

        int mid = (start + end) >> 1;
        return op1(query_range(node << 1, start, mid, l, r),
                   query_range(node << 1 | 1, mid + 1, end, l, r));
    }

    void push(int node, int start, int end)
    {
        if (lazy[node] == LLONG_MIN)
            return;  // Không có lazy
        tree[node] = (end - start + 1) * lazy[node];

        if (start != end)
        {
            lazy[node << 1]     = lazy[node];
            lazy[node << 1 | 1] = lazy[node];
        Ư
        lazy[node] = LLONG_MIN;
    }
};
