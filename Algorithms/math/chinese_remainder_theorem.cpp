ll exteuclid(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = exteuclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}
ll inv_mod(ll a, ll m)
{
    ll x, y;
    ll d = exteuclid(a, m, x, y);
    if (d != 1) return -1;
    x = (x % m + m) % m; 
    return x;
}



struct Congruence
{
    int a, m;
};

ll CRT(vector<Congruence> & c)
{
    ll M = 1;
    for (auto [a, m] : c) M *= m;

    ll sol = 0;
    for (auto [a, m] : c) {

        ll M1 = M / m;
        ll N1 = inv_mod(M1, m);
        sol = (sol + a * M1 % M * N1 % M) % M;
    }
    return sol;
}
