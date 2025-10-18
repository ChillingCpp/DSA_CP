vector<int> manacher_odd(string& s)
{
    int n = s.size();
    s     = '#' + s + '*';
    vector<int> p(n + 2);
    int         l = 0, r = 1;
    for (int i = 1; i <= n; ++i)
    {
        p[i] = min(r - i, p[l + r - i]);
        while (i + p[i] <= n + 1 && i - p[i] >= 0 && s[i + p[i]] == s[i - p[i]])
            p[i]++;
        if (i + p[i] > r)
        {
            l = i - p[i];
            r = i + p[i];
        }
    }
    return vector<int>(p.begin() + 1, p.end() - 1);
}
int manacher(string& s)
{
    int n = s.size();

    int ans = 0;
    string      t;
    for (auto c : s){
        t += '#';
        t += c;
    }
    t += '#';
    vector<int> p = manacher_odd(t);
    for (int i = 0; i < n; ++i)
        ans = max({ans, p[2 * i + 1], p[2 * i] - 1});

    return ans;
}
