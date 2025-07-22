// suitable for aho-corasick
struct Trie
{
    struct Node
    {
        array<int, 26> nxt;
        int            cnt;
        bool           end;
        Node()
        : cnt(0)
        , end(0)
        {
            fill(nxt.begin(), nxt.end(), 0);
        }
    };
    vector<Node> t{ Node() };
    Trie()
    {
    }
    void add(const string& s)
    {
        int idx = 0;
        for (auto& c : s)
        {
            int id = c - 'a';
            if (!t[idx].nxt[id])
            {
                t[idx].nxt[id] = t.size();
                t.emplace_back();
            }
            idx = t[idx].nxt[id];
            t[idx].cnt++;
        }
        t[idx].end = 1;
    }
    bool search(const string& s)
    {
        int idx = 0;
        for (auto& c : s)
        {
            int id = c - 'a';
            if (!t[idx].nxt[id])
                return false;
            idx = t[idx].nxt[id];
        }
        return t[idx].end;
    }
    bool isprefix(const string& s)
    {
        int idx = 0;
        for (auto& c : s)
        {
            int id = c - 'a';
            if (!t[idx].nxt[id])
                return false;
            idx = t[idx].nxt[id];
        }
        return true;
    }
    void print()
    {
        for (auto& i : t)
        {
            for (auto j : i.nxt)
                cout << j << ' ';
            cout << '\n';
        }
    }
    Trie& operator+=(const Trie& other)
    {
        merge(other);
        return *this;
    }
    Trie operator+(const Trie& other)
    {
        Trie& res = *this;
        res += other;
        return res;
    }

private:
    void merge(const Trie& other)
    {
        if (other.t.size() == 1)
            return;
        mergehelper(0, 0, other);
    }
    void mergehelper(int i1, int i2, const Trie& other)
    {
        if (other.t[i2].end)
        {
            t[i1].end = true;
            t[i1].cnt += other.t[i2].cnt;
        }
        for (int i = 0; i < 26; ++i)
        {
            int  i4 = other.t[i2].nxt[i];
            int& i3 = t[i1].nxt[i];
            if (!i4)
                continue;
            if (!t[i1].nxt[i])
            {
                i3 = t.size();
                copybranch(i4, other);
            }
            else
                mergehelper(i3, i4, other);
        }
    }
    void copybranch(int i2, const Trie& other)
    {
        // Create new node
        int i1 = t.size();
        t.emplace_back();

        // Copy node properties
        t[i1].end = other.t[i2].end;
        t[i1].cnt = other.t[i2].cnt;

        // Recursively copy children
        for (int i = 0; i < 26; i++)
        {
            if (other.t[i2].nxt[i])
            {
                t[i1].nxt[i] = t.size();
                copybranch(other.t[i2].nxt[i], other);
            }
        }
    }
};

// cannot combine with aho-corasick
struct Trie
{
    int                            size;
    std::vector<std::vector<int>>  nodes;
    std::vector<std::vector<bool>> eow;
    int                            n;
    int                            charsize = 26;
 
 
    Trie(int MAXN)
    : size(0)
    , n(MAXN)
    {
        nodes.assign(MAXN, vector<int>(charsize, 0));
        eow.assign(MAXN, vector<bool>(charsize, 0));
    }
 
    void add(const string& s)
    {
        int idx = 0;
        for (auto& c : s)
        {
            int id = c - 'a';
            nodes[idx][id]++;
            idx++;
        }
        eow[idx - 1][s[s.size() - 1] - 'a'] = true;
        size++;
    }
    bool search(const string& s)
    {
        int idx = 0;
        for (auto& c : s)
        {
            int id = c - 'a';
            if (!nodes[idx][id])
                return 0;
            idx++;
        }
        return eow[idx - 1][s[s.size() - 1] - 'a'];
    }
    
    bool isprefix(const string& s)
    {
        int idx = 0;
        if (s.size() > n)
            return false;
        for (char c : s)
        {
            int id = c - 'a';
            if (!nodes[idx][id])
                return false;
            idx++;
        }
        return true;
    }
 
    Trie& operator+=(Trie& ano)
    {
        if (ano.n > n)
        {
            swap(ano.nodes, nodes);
            swap(ano.eow, eow);
            swap(ano.n, n);
        }
        // ano.n <= n
        for (int i = 0; i < ano.n; ++i)
        {
            for (int j = 0; j < charsize; ++j)
            {
                nodes[i][j] += ano.nodes[i][j];
                eow[i][j] = eow[i][j] || ano.eow[i][j];
            }
        }
        size += ano.size;
        return *this;
    }
    Trie operator+(Trie& b)
    {
        Trie ret = (*this);
        ret += b;
        return ret;
    }
};
