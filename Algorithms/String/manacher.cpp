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

void manacherv2(string& s)
{
    int                 n = s.size();
    vector<vector<int>> p(2, vector<int>(n, 0));
    for (int z = 0; z < 2; z++)
    {
        int l = 0, r = 0;
        for (int i = 0; i < n; i++)
        {
            if (i < r)
                p[z][i] = min(r - i + !z, p[z][l + r - i + !z]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1])
                p[z][i]++, L--, R++;
            if (R > r)
                l = L, r = R;
        }
    }
}
