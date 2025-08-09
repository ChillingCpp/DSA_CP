
// some math function for cp
ll binmod(ll a, ll b, ll mod)
{
    a %= mod;
    ll res = 1;
    while (b){
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
    }
}
ll nCk(ll n, ll k)
{
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
    k = min(k, n - k);
    ll res = 1;
    for (ll i = 1; i <= k; ++i)
    {
        res = res * (n - i + 1) / i;
    }
    return res;
}
