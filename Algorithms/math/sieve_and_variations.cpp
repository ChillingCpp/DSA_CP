// template for some problems using sieve, O(n log n)
void sieve_template(){

    int n = 1e6;
    vector<int> sieve(n+1, 1);
    for (int i = 2; i <= n; ++i)
    {
        for (int j = i; j <= n; j += i)
            // compute something with i, 2i, 3i, 4i,... , like the f(x) function 
    }
}
void segment_sieve(ll l, ll r)
{
    int sqr = sqrt(r);
    /// sieve 1 to sqrt(r)
    vector<bool> mark(sqr + 1, 1);
    vector<ll> sieve(r - l + 1, true), primes, pri;
    prime.reserve(r - l + 1);
    pri.reserve(r - l + 1);
    for (int i = 2; i <= sqr; ++i)
    {
        if (mark[i]){
            pri.push_back(i);
            for (int j = i * i; j <= n; j += i) 
                mark[j] = 0;
        }
    }

    for (auto p : pri)
        for (int j = max(p * p, (l + p - 1) / (p * p)); j <= R; j += p)
            sieve[j - l] = false;
    
    if (l == 1) 
        sieve[0] = false;
    for (int i = l; i <= R; ++i) 
        if (sieve[i - l]) 
            primes.push_back(i);
}


//// all in one sieve from [1...n]
int                 n = 1e6 + 2;
vector<int>         prime(n, 1), divcnt(n, 1), divsum(n, 1), f(n), phi(n), spf(n), bpf(n);
vector<vector<int>> divlist(n, { 1 });

void all_sieve()
{
    divsum[0] = prime[0] = prime[1] = 0;

    divcnt[0] = 0;
    f[0] = f[1] = 1;  /// compute somthing about f(x)
    divlist[0]  = {};

    iota(spf.begin(), spf.end(), 0);
    iota(bpf.begin(), bpf.end(), 0);
    iota(phi.begin(), phi.end(), 0);

    // i* i <= n only for prime sieve
    /// O(n log log n)
    for (int i = 2; i * i <= n; ++i)
    {
        if (prime[i])
            for (int j = i * i; j <= n; j += i)
                prime[j] = 0;
    }

    /// O(n log log n)
    for (int i = 2; i <= n; ++i)
    {
        if (spf[i] == i)
            for (int j = i; j <= n; j += i)
            {
                if (spf[j] == j) spf[j] = i;
                bpf[j] = i;
                phi[j] -= phi[j] / i;
            }
    }
    /// O(n log n)
    for (int i = 2; i <= n; ++i)
    {
        f[i] = ...;  /// calculate f[i]
        for (int j = i; j <= n; j += i)
        {
            if (i != j){
                f[j] = ...;  /// calc f[2*i], f[3*i].... base on f[i]
                f[i] = ...;  /// or vice versa
            }

            divcnt[j]++;
            divsum[j] += i;
            divlist[j].push_back(i);
        }
    }
}

