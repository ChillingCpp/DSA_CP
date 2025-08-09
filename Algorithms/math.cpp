
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
        res = res * (n - i + 1) / i;
    return res;
}

ll nCk(ll n, ll k, ll mod)
{
    // mod is prime
    if (k > n || k < 0) return 0;
    k = min(k, n - k);
    ll num = 1, denom = 1;
    for (ll i = 1; i <= k; ++i)
    {
        num = (num * (n - i + 1)) % mod;
        denom = (denom * i) % mod;
    }
    ll invdenom = binmod(denom, mod - 2, mod);
    return (num * invdenom) % mod;
}

// lucas_theorem : use for n >= mod. this vase very rare
ll lucas_nCk(ll n, ll k, ll mod)
{
    // mod is prime
    if (k > n || k < 0) return 0;
    k = min(k, n - k);
    ll res = 1;
    while (n || k)
    {
        ll ni = n % mod;
        ll ki = k % mod;
        res = (res * nCk(ni, ki, mod)) % p;
        if (res == 0) return 0;
        n /= p;
        k /= p;
    }
    return res;
}

// precompute fac and inv_fac in O(n)
ll n = 1e6;
vector<ll> fac(n + 1,1);
vector<ll> inv_fac(n +1, 1);
void precompute(ll mod)
{
    for (int i = 1; i <= n; ++i) 
        fac[i] = (i * fac[i-1]) % mod;
    inv_fac[n] = binmod(fac[n], mod - 2, mod);
    for (int i = n-1; i > 0; --i) 
        inv_fac[i] = (inv_fac[i+1] * i) % mod;
}
