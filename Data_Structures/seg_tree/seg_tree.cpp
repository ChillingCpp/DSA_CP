// normal segment tree
struct Node
{
};
Node combine(Node a, Node b)
{
    return Node();
}
struct SegmentTree
{
    int          n = 1;
    vector<Node> st;
    SegmentTree(vector<Node>& a)
    {
        int n1 = a.size();
        while (n <= n1)
            n <<= 1;
        st.resize(2 * n);
        std::copy(a.begin(), a.end(), st.begin() + n);
        for (int i = n - 1; i > 0; --i)
            st[i] = combine(st[i << 1], st[i << 1 | 1]);
    }
    void set(int p, Node val)
    {
        st[p += n] = val;
        for (p >>= 1; p; p >>= 1)
            st[p] = combine(st[p << 1], st[p << 1 | 1]);
    }
    Node query(int l, int r)
    {
        Node res;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = combine(res, st[l++]);
            if (r & 1)
                res = combine(st[--r], res);
        }
        return res;
    }
};

