struct aho_corasick
{
    struct node
    {
        int            link = -1, exit = -1;
        array<int, 26> nxt;
        vector<int>    leaf;
        node()
        {
            fill(nxt.begin(), nxt.end(), 0);
        }
    };
    vector<node> g = { node() };
    // sidx : index of the string in pattern list
    void         insert_string(const string& s, int sidx)
    {
        int p = 0;
        for (char c : s)
        {
            if (!g[p].nxt[c])
            {
                g[p].nxt[c] = g.size();
                g.emplace_back();
            }
            p = g[p].nxt[c];
        }
        g[p].leaf.push_back(sidx);
    }

    void build_automaton()
    {
        queue<int> q;
        for (q.push(0); q.size(); q.pop())
        {
            // process the front node in queue
            int curr = q.front(), link = g[curr].link;
            if (curr)
                g[curr].exit = g[link].leaf.size() ? link : g[link].exit;
            for (int i = 0; i < 26; i++)
            {
                int &nxt = g[curr].nxt[i], nxt_sf = curr ? g[link].nxt[i] : 0;
                if (nxt == -1)
                    nxt = nxt_sf;
                else
                {
                    g[nxt].link = nxt_sf;
                    q.push(nxt);
                }
            }
        }
    }
    vector<int> get_sindex(int p)
    {
        vector<int> a;
        for (int v = g[p].leaf.size() ? p : g[p].exit; v != -1; v = g[v].exit)
            for (int j : g[v].leaf)
                a.push_back(j);
        return a;
    }
};
