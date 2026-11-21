//// work with non negative number, for bitwise operation
struct BitTrie
{
    struct Node
    {
        int l, r;
        int c;
    };
    vector<Node> t;
    BitTrie()
    {
        t.push_back({ -1, -1, 0 });  // root
    }
    int createNode(int root)
    {
        if (root == -1)
            t.push_back({ -1, -1, 1 }), root = t.size() - 1;
        else
            t[root].c++;
        return root;
    }
    void insert(int num)
    {
        int cur = 0;
        for (int i = 30; i >= 0; --i)
        {
            int nxt = -1;
            if ((1 << i) & num)
                nxt = createNode(t[cur].r), t[cur].r = nxt;
            else
                nxt = createNode(t[cur].l), t[cur].l = nxt;
            cur = nxt;
        }
    }
    int cnthelper(int cur, int i, int bl, int pr, int k)
    {
        if (cur == -1 || i < 0)
            return 0;
        int ans = 0;
        int bk  = ((1 << i) & k) >> i;
        int br  = ((1 << i) & pr) >> i;
        int b   = bl ^ br;
        if (i == 0 && b == bk)
            return t[cur].c;

        if (bk == b)
        {
            ans += cnthelper(t[cur].l, i - 1, 0, pr, k);
            ans += cnthelper(t[cur].r, i - 1, 1, pr, k);
        }
        if (b && !bk)
            ans += t[cur].c;

        return ans;
    }
    int count(int pr, int k)
    {
        /// count bl that bl ^ pr >=  k;
        int ans = 0;
        ans += cnthelper(t[0].r, 30, 1, pr, k);
        ans += cnthelper(t[0].l, 30, 0, pr, k);
        return ans;
    }
};
