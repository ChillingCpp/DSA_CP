struct aho_corasick
{
    struct node
    {
        int            link = -1, exit = -1;
        array<int, 26> nxt;
        vector<int>    leaf;
        node()
        {
            fill(nxt.begin(), nxt.end(), -1);
        }
    };
    vector<node> t = { node() };
    // sidx : index of the string in pattern list
    void insert_string(const string& s, int sidx)
    {
        int p = 0;
        for (char c : s)
        {
            if (t[p].nxt[c] == -1)
            {
                t[p].nxt[c] = t.size();
                t.emplace_back();
            }
            p = t[p].nxt[c];
        }
        // store index ends at p;
        t[p].leaf.push_back(sidx);
    }

    void build_automaton()
    {
        queue<int> q;
        for (q.push(0); q.size(); q.pop())
        {
            // process the front node in queue
            int curr = q.front(), link = t[curr].link;
            if (curr)
                t[curr].exit = t[link].leaf.size() ? link : t[link].exit;
            for (int i = 0; i < 26; i++)
            {
                int &nxt = t[curr].nxt[i], nxt_sf = curr ? t[link].nxt[i] : 0;
                if (nxt == -1)
                    nxt = nxt_sf;
                else
                {
                    t[nxt].link = nxt_sf;
                    q.push(nxt);
                }
            }
        }
    }
    vector<int> get_sindex(int p)
    {
        vector<int> a;
        for (int v = t[p].leaf.size() ? p : t[p].exit; v != -1; v = t[v].exit)
            for (int j : t[v].leaf)
                a.push_back(j);
        return a;
    }
};
