// template for some problems using sieve, mean try to do something with 2n, 3n, 4n,... with n is prime or not
void sieve_template(){

    int n = 1e6;
    vector<int> sieve(n+1, 1);
    sieve[0] = sieve[1] = 0;
    for (int i = 2; i *i <= n; ++i)
    {
        if (sieve[i])
        for (int j = i * 2; j <= n; j += i)
            // compute something with i, 2i, 3i, 4i,... 
    }
}

int n = 1e6; // can up to 1e7 - 1e8
vector<int> sieve(n + 1, 1);
void normal_sieve(){
    sieve[0] = sieve[1] = 0;
    for (int i = 2; i * i <= n; ++i)
    {
        if (sieve[i]) 
        for (int j = i * i; j <= n; j += i) 
            sieve[j] = 0;
    }
}
void segment_sieve(ll l, ll r)
{
    int sqr = sqrt(r);
    /// sieve 1 to sqrt(r)
    vector<bool> mark(sqr + 1, 1);
    vector<ll> sieve(r - l + 1, true), primes, pri;
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


// smallest prime factor, help factoring a number in O(log n)
int n = 1e6; // can up to 1e7 - 1e8
vector<int> spf(n + 1, 0);
void compute_spf(){
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; i * i <= n; ++i)
    {
        if (spf[i] == i) 
        for (int j = i * i; j <= n; j += i) 
            if (spf[j] == j) 
                spf[j] = i;
    }
}
// euler totient
int n = 1e6; // can up to 1e7 - 1e8
vector<int> phi(n + 1, 0);
void        compute_phi()
{
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i <= n; ++i)
    {
        if (phi[i] == i)
        for (int j = i; j <= n; j += i)
            phi[j] -= phi[j] / i;  // phi[j] *= (i - 1) / i;
    }
}


