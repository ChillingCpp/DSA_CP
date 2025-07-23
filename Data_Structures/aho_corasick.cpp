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
            if (!t[p].nxt[c])
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
            int cur = q.front(), link = t[cur].link;  // point to the longest proper prefix
            if (cur)
                t[cur].exit = t[link].leaf.size() ? link : t[link].exit;
            for (int i = 0; i < 26; ++i)
            {
                int &nxt = t[cur].nxt[i], nxt_sf = cur ? t[link].nxt[i] : 0;
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
    // If I'm currently at state X and I see character C, which state should I move to?
    int go(int state, char c)
    {
        int cidx = c - 'a';

        // Follow failure links until we find a valid transition
        while (state != -1 && t[state].nxt[cidx] == -1)
            state = t[state].link;  // Follow failure link

        // If we fell off the trie, go to root; otherwise use the transition
        return (state == -1) ? 0 : t[state].nxt[cidx];
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
