

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

// a*x + b*y = c
bool solveequ(ll a, ll b, ll c, ll&x0, ll& y0)
{
    ll g = euclid(abs(a), abs(b), x0, y0);
    if (c % g) return false;

    x0 *= (c / g);
    y0 *= (c / g);
    return true;
}
// y = ax + b;
struct linear
{
    ll a = 0, b =0 ;
};
bool solveequ(ll a, ll b, ll c, ll&x0, ll& y0, linear& s1, linear& s2)
{
    ll g = euclid(abs(a), abs(b), x0, y0);
    if (c % g) return false;

    a /= g;
    b /= g;
    c /= g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    s1.a = b;
    s1.b = x0 * c;
    
    s2.a = -a;
    s2.b = y0 * c;
    return true;
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
