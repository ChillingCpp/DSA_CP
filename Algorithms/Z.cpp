vector<int> Z(const string& p)
{
    int n = p.size();
    vector<int> z(n);
    z[0]  = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i)
    {
        if (i < r)
        {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && p[z[i]] == p[i + z[i]])
            z[i]++;
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
