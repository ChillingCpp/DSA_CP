
vector<int> kmp(const string& s)
{
    int n = s.size();
    vector<int> lps(n);
    for (int i = 1; i < n; ++i)
    {
        int j = lps[i-1];
        while (j > 0 && s[j] != s[i]) j = lps[j-1];
        lps[i] = j + s[i] == s[j];
    }
    return lps;
}
