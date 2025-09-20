// examples : CF 309C


// tư tưởng như sau : các vị trí i có thể phân rã cho các vị trí j < i, và từ tư tưởng đó thì tốt nhất ta nên lan truyền xuống j nếu j không đủ
// mỗi lần truyền thì có thể vị trí j sẽ luôn được >= i, vậy nên tham lam hoạt động tốt trong trường hợp này.
/// duyệt iter 2 lần hoặc n lần đảm bảo được lan truyền hoàn toàn.

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    vector<int> freqa(32), freqb(32);
    for (auto& i : a)
    {
        cin >> i;
        for (int j = 30; j >= 0; --j)
            if ((i >> j) & 1)
                freqa[j]++;
    }
    for (auto& i : b)
    {
        cin >> i;
        freqb[i]++;
    }

    int cnt = 0;

    for (int iter = 0; iter <= 1; ++iter)
        for (int i = 0; i <= 30; ++i)
            if (freqa[i] > freqb[i])
                for (int j = i - 1; j >= 0 && freqa[i] > freqb[i]; --j)
                {
                    if (freqa[j] >= freqb[j])
                        continue;
                    int diff = freqb[j] - freqa[j];
                    int val  = (1 << (i - j));
                    int num  = (diff + val - 1) / val;
                    diff -= min(num, freqa[i]) * val;
                    freqa[j] += min(num, freqa[i]) * val;
                    freqa[i] -= min(num, freqa[i]);
                }
    for (int iter = 0; iter <= 1; ++iter)
        for (int i = 0; i <= 30; ++i)
            for (int j = i - 1; j >= 0; --j)
            {
                if (freqa[j] >= freqb[j])
                    continue;
                int diff = freqb[j] - freqa[j];
                int val  = (1 << (i - j));
                int num  = (diff + val - 1) / val;
                diff -= min(num, freqa[i]) * val;
                freqa[j] += min(num, freqa[i]) * val;
                freqa[i] -= min(num, freqa[i]);
            }

    for (int i = 0; i <= 30; ++i)
        cnt += min(freqa[i], freqb[i]);
    cout << cnt << '\n';
}
