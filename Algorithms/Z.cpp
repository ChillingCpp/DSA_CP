void Z(const string& s, const string& p)
{
    string s1 = p + '#' + s;

    int n = s1.size();

    vector<int> z(n);
    z[0]  = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i)
    {
        if (i < r)
        {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s1[z[i]] == s1[i + z[i]])
            z[i]++;
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
    int ans = 0;
    for (int i = p.size() + 1; i < n; ++i)
    {
        if (z[i] == p.size())
            ans++;
    }
    cout << ans << '\n';
}
