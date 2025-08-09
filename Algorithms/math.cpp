
// some math function for cp
ll binmod(ll a, ll b, ll mod)
{
    a %= mod;
    ll res = 1;
    while (b){
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

ll nCk(ll n, ll k)
{
    if (k > n || k < 0) return 0;
    k = min(k, n - k);
    ll res = 1;
    for (ll i = 1; i <= k; ++i)
    {
        res = res * (n - i + 1) / i;
    }
    return res;
}

ll nCk(ll n, ll k, ll mod)
{
    // mod is prime
    if (k > n || k < 0) return 0;
    k = min(k, n - k);
    ll nume = 1, denom = 1;
    for (ll i = 1; i <= k; ++i)
    {
        nume = (nume * (n - i + 1)) % mod;
        denom = (denom * i)) % mod;
    }
    ll invdenom = binmod(denom, mod - 2, mod);
    return (nume / denom) % mod;
}
