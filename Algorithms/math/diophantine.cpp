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
    ll a = 0, b = 0; /// solution of diophantine can be represent as linear equaltion, x is an integer
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
