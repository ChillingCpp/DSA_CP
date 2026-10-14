struct DST
{
    struct Val { ll val = 0; };
    Val idn() { return Val(); }
    Val op(Val a, Val b){ return { a.val + b.val }; }
    vector<vector<Val>> tab;
    DST() = default;
    DST(const vi& a)
    {
        vector<Val> b;

        int n  = a.size();
        int nr = 1 << (__lg(n) + 1);
        for (auto& i : a)
            b.push_back({ i });
        for (; b.size() < nr; b.push_back(idn()))
            ;
        tab.assign(__lg(n) + 1, vector<Val>(nr));
        for (int level = 0; level < tab.size(); ++level)
            for (int block = 0; block < nr / (1 << (level + 1)); ++block)
            {
                int start = (1 << (level + 1)) * block;
                int end   = (1 << (level + 1)) * (block + 1) - 1;
                int mid   = (start + end) / 2;

                /// suffix
                tab[level][mid] = b[mid];
                for (int i = mid - 1; i >= start; --i)
                    tab[level][i] = op(b[i], tab[level][i + 1]);

                /// prefix
                tab[level][mid + 1] = b[mid + 1];
                for (int i = mid + 2; i <= end; ++i)
                    tab[level][i] = op(tab[level][i - 1], b[i]);
            }
        
    }
    Val query(int l, int r)
    {
        if (l > r) return idn();
        if (l == r) return tab[0][l];
        int level = __lg(l ^ r);
        return op(tab[level][l], tab[level][r]);
    }
};
