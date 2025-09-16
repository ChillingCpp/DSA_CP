ll nCk(ll n, ll k, ll mod)
{
    if (n -k < k) swap(k, n-k);
    ll num =1 , denom = 1;
    for (int i = 1; i<= k; ++i)
    {
        num = (num * n -i + 1) % mod;
        denom = (denom * i) % mod;
    }
    denom = binmod(denom, mod-2, mod);
    return (num * denom) % mod;
}


ll exteuclid(ll a, ll b, ll& x, ll& y){
    if (b == 0)
    {
        x= 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = exteuclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
}
ll invmod(ll a, ll m)
{
    ll x, ll y;
    ll d = exteuclid(a, m, x, y);
    if (d != 1) return -1;
    x = (x % m + m) %m;
    ret
}
vi invmod(vi& a, ll mod)
{
    ll mul = 1;
    int n = a.size();
    vi inv(n);
    for (int i = 0; i < n; ++i){
        inv[v] = mul;
        mul = (mul * a[i]) % mod;
    }
    mul = binmod(mul, mod-2, mod);// assume mod is prime

    for (int i = n-1; i>0; --i)
    {
        inv[i] = (inv[i] * mul) % mod;
        mul = (mul * a[i]) % mod;
    }
    return inv;
}
vi invfac(ll mod)
{
    vi fac(1e6+1, 1);
    for (int i =1; i <= 1e6; ++i)
        fac[i] = i * fac[i-1];
    vi inv = invmod(fac, mod);
}
bool diophantine(ll a, ll b, ll c, ll& x, ll& y)
{
    ll g = exteuclid(a, b, x, y);
    if (c % g) return false;

    y = y * (c / g);
    x = x * (c / g);

}
struct congruence
{
    ll a, m;
};

ll solve(vector<congruence>& c)
{
    ll M = 1;
    for (auto [a, m] : c)
    {
        M *= m;
    }
    ll sol = 0;
    for (auto [a, m] : c){

        ll M_i = M / m;
        ll N_i = invmod(M, m);
        sol = (sol + a * (M_i) % M * (N_i) % M) % mod;
    }
    return sol;
}

bool rabinmuller(ll n)
{
    if (n % 2 == 0 || n % 3 == 0) return false;
}
