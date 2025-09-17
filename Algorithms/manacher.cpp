vector<int> manacher_odd(string& s)
{
    int n = s.size();
    s     = '#' + s + '*';
    vector<int> p(n + 2);
    int         l = 0, r = 1;
    for (int i = 1; i <= n; ++i)
    {
        p[i] = min(r - i, p[l + r - i]);
        while (s[i + p[i]] == s[i - p[i]])
            p[i]++;
        if (i + p[i] > r)
        {
            l = i - p[i];
            r = i + p[i];
        }
    }
    return vector<int>(p.begin() + 1, p.end() - 1);
}
vector<int> manacher(string& s)
{
    int n = s.size();

    vector<int> ans(n);
    string      t;
    for (auto c : s)
        t += string('#', 1) + c;
    t += '#';
    vector<int> p = manacher_odd(t);
    for (int i = 0; i < n; ++i)
        ans[i] = max(p[2 * i + 1] / 2, (p[2 * i] - 1) / 2);

    return ans;
}
