using ll = long long;
ll binmod(ll a, ll b, ll mod)
{
    a %= mod;
    ll res = 1;
    for (; k; a = (a*a) % mod, k >>= 1)
        if (k & 1) 
            res = (res * a) % mod;
    return res;
}
// try to compute a^m % n == 1 or == n - 1 or a^((2^l)*m) % n == n - 1
bool test(ll a, ll n, ll k, ll m){

    ll mod = binmod(a, m, n);
    if (mod == 1 || mod == n - 1) return true;
    for (int l = 1; l < k; ++l){
        mod = (mod * mod) % n;
        if (mod == n-1) return true;
    }
    return false;
}
bool rabinMuller(ll n){

    if (n % 2 == 0 || n % 3 == 0) return false;

    vector<ll> check = {2,3,5,7,11,13,17,19,23,29,31,37};
    if (*lower_bound(check.begin(), check.end(), n) == n) return true;

    if (n < 41) return false;

    ll m = n-1, k = 0;
    while (m % 2 == 0) {
        m /=2;
        k++;
    }
    for (auto a : check)
        if (!test(a, n, k, m)) return false;
        
    return true;
}
