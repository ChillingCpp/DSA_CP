
vector<vector<int>> a;
vector<int>         in, out;
vector<int>         path;

void dfs(int u)
{
    stack<int> st;
    st.push(u);
    while (st.size())
    {
        int p = st.top();
        if (out[p])
            st.push(a[p][--out[p]);
        else {
            path.push_back(p);
            st.pop();
        }
    }
}
void euler()
{
    int n = a.size();
    for (int i = 0; i < n; ++i)
    {
        for (auto j : a[i])
        {
            out[i]++;
            in[j]++;
        }
    }
    bool c1 = false, c2 = false, no = false;
    int  start = 1;
    for (int i = 0; i < n; ++i)
    {
        if (out[i] - in[i] > 1 || in[i] - out[i] > 1)
            no = true;
        if (out[i] - in[i] == 1)
        {
            if (c1)
                no = true;
            c1    = true;
            start = i;
        }
        if (in[i] - out[i] == 1)
        {
            if (c2)
                no = true;
            c2 = true;
        }
    }
    if (no)
        return;
    dfs(start);
}
