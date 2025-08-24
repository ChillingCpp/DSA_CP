

ll euclid(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b); 
}

ll invmod(ll a, ll b, ll m){

    ll x, y;
    ll d = euclid(a, b, x, y);
    if (d != 1) return -1;
    x = (x % m + m) % m;
    return x;
}

vector<ll> invmod(vector<ll> a, ll b, ll m)
{
    ll n = a.size();
    ll v = 1;
    vector<ll> inv(n, 0);
    for(ll i = 0; i < n; ++i){
        inv[i] = v;
        v = (v * a[i]) % m;
    }
    v = modInv(v, m);
    for(ll i = n - 1; i >= 0; --i){
        inv[i] = (1ll * inv[i] * v) % m;
        v = (v * a[i]) % m;
    }
    return inv;

}

