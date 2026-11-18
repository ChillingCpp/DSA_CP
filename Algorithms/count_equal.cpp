
// đếm số phần tử trong đoạn [l, r] bằng với k
map<int, vector<int>> mp;
for (int i = 1; i <= n; ++i)
    mp[a[i]].push_back(i);
/// query (l, r, k) đếm số phần tử = k
auto query = [&](int l, int r, int k) -> int
{
    if (mp.find(k) == mp.end())
        return 0;
    return upper_bound(all(mp[k]), r) - lower_bound(all(mp[k]), l);
};
