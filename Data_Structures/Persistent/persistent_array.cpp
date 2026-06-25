struct Perarr
{
    vector<vector<pair<int, int>>> v;
    int                            t = 0;
    Perarr(vi& a)
    {
        v.resize(a.size());
        for (int i = 0; i < a.size(); ++i)
            v[i].push_back({ 0, a[i] });
    }
    int get(int id, int time)
    {
        return (upper_bound(v[id].begin(), v[id].end(), make_pair(time, INT_MAX)) - 1)->second;
    }
    void update(int id, int val)
    {
        v[id].push_back({ ++t, val });
    }
};
