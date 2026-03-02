

/// this is mean we can process each bit one by one from MSB downto LSB
/// constraint : if bit can be solved indenpendently for all n integers
/// time complexity : O(30 * n)
/// if we not use bit contribution then time complexity is O(n^2) or more

const int bitsz = 30;  /// for 1e9
ll        mod   = 1e9 + 7;
vi        cnt(bitsz + 1);

// example : sum xor of all subarray
for (int k = bitsz; k >= 0; --k)
{
    ll  c[2] = { 1, 0 };
    int b    = 0;
    for (int i = 0; i < n; ++i)
    {
        int bit = (a[i] >> k) & 1;
        b ^= bit;
        cnt[k] += c[b ^ 1];
        c[b]++;
    }
}
ll ans = 0;
for (int i = 0; i <= bitsz; ++i)
    ans = (ans + cnt[i] * (1ll << i)) % mod;
cout << ans << '\n';
