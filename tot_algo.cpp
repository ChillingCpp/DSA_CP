/*
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

void sieve(ll L, ll R)
{
    ll sqrtR = sqrt(R);
    vi mark(sqrtR+1, 1), primes;
    vi res(R - L + 1, 1);
    mark[0] = mark[1] = false;
    for (int i = 2; i <= sqrtR; ++i)
    {
        if (!mark[i]) continue;
        primes.push_back(i);
        for (int j = i * i; j <= sqrtR; j += i)
        {
            mark[j] = false;
        }
    }
    for (auto p : primes)
    {

        for (int j = max(p * p, (L + p - 1) / p * p); j <= R; j += p)
            res[j - L] = false;
    }
    if (L == 1) res[0] = false;

}


void all_sieve()
{
    int n= 1e6;
    vi phi(n+1);
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i <= n; ++i)
    {
        if (phi[i] == i)
        {

            for (int j = i; j <= n; j += i)
            {
                phi[j] -= phi[j] / i;

            }
        }
    }
}


void kmp(string& s)
{
    int n = s.size();
    vi lps(n);
    for (int i = 1; i <n; ++i)
    {
        int j = lps[i-1];
        while (j > 0 && s[i] != s[j]) j = lps[j-1];
        lps[i] += j + (s[i] == s[j]);
    }
    // interesting properties :
    // lps[n-1], lps[lps[n-1]-1]... is when prefix = suffix
}


void Z(string& s)
{
    int n  = s.size();
    vi z(n);
    z[0] = n;
    int l =0 , r = 0;
    for (int i = 1; i < n; ++i)
    {
        if (i < r)
            z[i] = min(r - l, z[i-l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
}


struct Hash
{
    ull base1 = 737, base2 = 1009;
    ull mod = 1e9 + 7;
    static vui p1;
    static vui p2;

    vui h1, h2;

    ull sub(ull a, ull b, ull mod)
    {
        return ((a - b) % mod + mod) % mod;
    }
    string a;
    int n;
    Hash(string &s)
    {
        a = s;
        n = a.size();
        h1.resize(n+1);
        h2.resize(n+1);
        int np = 1e6;
        if (p1.size() != np + 1){
            p1.assign(np + 1, 1);
            p2.assign(np + 1, 1);
            for (int i = 1; i <= np; ++i){
                p1[i] = (p1[i-1] * base1) % mod;
                p2[i] = p2[i-1] * base2;
            }
        }

        for (int i = 1; i <= n; ++i)
        {
            h1[i] = (h1[i-1] * base1 + a[i-1] - 'a' + 1) % mod;
            h2[i] = h2[i-1] * base2 + a[i-1] - 'a' + 1;
        }
    }
    pii getHash(int l, int r)
    {
        ll hash1 = sub(h1[r], (h1[l-1] * p1[r - l + 1]) % mod, mod);
        ll hash2 = h2[r] - h2[l-1] * p2[r - l + 1];
        return {hash1, hash2};
    }
};
vui Hash::p1{1};
vui Hash::p2{1};



void nextgreater(vector<int> &a)
{

    int n = a.size();
    stack<int> st;
    vector<int> ans(n);
    for (int i =n-1 ;i >=0; --i)
    {
        while (st.size() && a[st.top()] <= a[i])st.pop();

        ans[i] = (st.size()) ? a[st.top()] : -1;
        st.push(i);

    }
}

void boundarymax(vector<int> &a){

    int n = a.size();
    stack<int> st;
    vector<int> ans(n), l(n), r(n);
    for (int i =n-1 ;i >=0; --i)
    {
        while (st.size() && a[st.top()] <= a[i])st.pop();

        r[i] = (st.size() ? st.top() : n);
        st.push(i);

    }
    st= stack<int>();
    for (int i =0  ;i < n;++i)
    {
        while (st.size() && a[st.top()] <= a[i])st.pop();

        l[i] = (st.size() ? st.top() : -1); // outside
        st.push(i);
    }

    // now l[i] and r[i] is where the a[i] contribute as max element, interval have n * (n+1) /2 subinterval;
}
// less : sliding max, greater : sliding min

vi sliding(vector<int>& a, int k, function<ll(ll, ll)> cmp)
{
    int n = a.size();
    deque<int>dq;
    vi ans;
    for (int i = 0; i < k; ++i){

        while (dq.size() && cmp(a[dq.back()], a[i])) dq.pop_back();
        dq.push_back(i);
    }
    ans.push_back(a[dq.front()]);
    for (int i = k; i < n; ++i)
    {
        while (dq.size() && dq.front() < i - k + 1) dq.pop_front();
        while (dq.size() && cmp(a[dq.back()], a[i])) dq.pop_back();
        ans.push_back(a[dq.front()]);
        dq.push_back(i);
    }
    return ans;
}

struct DSU
{

    vi parent, sz;
    DSU(int n) : parent(n), sz(n, 1)
    {
        iota(parent.begin(), parent.end(), 0);
    }
}; */
