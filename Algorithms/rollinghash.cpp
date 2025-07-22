// rolling hash
// current best hash, can choose some random modulus in range 1e9 -> 2e9, and base from range 257 -> mod 
// can only be stored in set, map because hashing a pair is hard
struct DoublePhash
{
    static const ull mod1  = 1827349297;
    static const ull mod2  = 1927349317;
    static const ull base1 = 737;   // satisfy max(a[i]) < base1 < mod1;
    static const ull base2 = 1009;  // satisfy max(a[i]) < base2 < mod2;

    static vui p1, p2;

    vui h1;
    vui h2;

    int n;

    DoublePhash(const string& s)
    : h1(s.size() + 1)
    , h2(s.size() + 1)
    , n(s.size())
    {
        int mxpow = 1e6 + 2;
        if (p1.size() != mxpow)
        {
            p1.assign(mxpow, 1);
            p2.assign(mxpow, 1);
            for (int i = 1; i < mxpow; ++i)
            {
                p1[i] = (p1[i - 1] * base1) % mod1;
                p2[i] = (p2[i - 1] * base2) % mod2;
            }
        }
        for (int i = 1; i <= s.size(); ++i)
        {
            h1[i] = (h1[i - 1] * base1 + s[i - 1] - 'a' + 1) % mod1;
            h2[i] = (h2[i - 1] * base2 + s[i - 1] - 'a' + 1) % mod2;
        }
    }


    puii gethash(int l, int r)  // get hash [l...r]
    {
        ull hash1 = (h1[r] - h1[l - 1] * p1[r - l + 1]) % mod1;

        ull hash2 = (h2[r] - h2[l - 1] * p2[r - l + 1]) % mod2;
        if (hash1 < 0)
            hash1 += mod1;
        if (hash2 < 0)
            hash2 += mod2;
        return { hash1, hash2 };
    }
    puii gethash()
    {
        return { h1[n], h2[n] };
    }
};
vui DoublePhash::p1{ 1 };  // declare, do not forget this 2 lines of code
vui DoublePhash::p2{ 1 };


// with randome prime mod1 and mersenne prime 2^61 -1, fast modular trick O(1)
// hard to remember, but in some tricky case its needed
struct DoublePhashv2
{
    static const ull mod1  = 2027349299;
    static const ull mod2  = (1ll << 61) - 1;
    static const ull base1 = 737;   // satisfy max(a[i]) < base1 < mod1;
    static const ull base2 = 1009;  // satisfy max(a[i]) < base2 < mod2;

    static vui p1, p2;

    vui h1;
    vui h2;

    int n;

    ull add(ull a, ull b, ull mod)
    {
        return (a += b) >= mod ? a - mod : a;
    }
    ull sub(ull a, ull b, ull mod)
    {
        return a >= b ? a - b : a + mod - b;
    }
    ull mul(ull a, ull b)
    {
        // especially for 2^61 - 1
        ull l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
        ull l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
        ull ret = (l & mod2) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        ret     = (ret & mod2) + (ret >> 61);
        ret     = (ret & mod2) + (ret >> 61);
        return ret - 1;
    }
    DoublePhashv2(const string& s)
    : h1(s.size() + 1)
    , h2(s.size() + 1)
    , n(s.size())
    {
        int mxpow = 1e6 + 2;
        if (p1.size() != mxpow)
        {
            p1.assign(mxpow, 1);
            p2.assign(mxpow, 1);
            for (int i = 1; i < mxpow; ++i)
            {
                p1[i] = (p1[i - 1] * base1) % mod1;
                p2[i] = mul(p2[i - 1], base2);
            }
        }
        for (int i = 1; i <= s.size(); ++i)
        {
            h1[i] = (h1[i - 1] * base1 + s[i - 1] - 'a' + 1) % mod1;
            h2[i] = add(mul(h2[i - 1], base2), s[i - 1] - 'a' + 1, mod2);
        }
    }


    puii gethash(int l, int r)  // get hash [l...r]
    {
        ull hash1 = sub(h1[r], h1[l - 1] * p1[r - l + 1], mod1);

        ull hash2 = sub(h2[r], mul(h2[l - 1], p2[r - l + 1]), mod2);

        return { hash1, hash2 };
    }
    puii gethash()
    {
        return { h1[n], h2[n] };
    }
};
vui DoublePhashv2::p1{ 1 };  // declare, do not forget this 2 lines of code
vui DoublePhashv2::p2{ 1 };

// Phash 64 bits, hard to remember but faster than DoublePhash when mapping 
struct Phash
{
    static const ull mod  = (1ull << 61) - 1;
    static const ull base = 1009;  // satisfy max(a[i]) < base < mod;
    static vui       p;

    vui h;
    int n;
    Phash(const string& s)
    : h(s.size() + 1)
    , n(s.size())
    {
        int mxpow = 1e6 + 2;
        if (p.size() != mxpow)
        {
            p.assign(mxpow, 1);
            for (int i = 1; i < mxpow; ++i)
            {
                p[i] = mul(p[i - 1], base);
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            h[i] = add(mul(h[i - 1], base), s[i - 1] - 'a' + 1);
        }
    }

    ull add(ull a, ull b)
    {
        return (a += b) >= mod ? a - mod : a;
    }
    ull sub(ull a, ull b)
    {
        return a >= b ? a - b : a + mod - b;
    }
    ull mul(ull a, ull b)
    {
        // especially for 2^61 - 1
        ull l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
        ull l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
        ull ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        ret     = (ret & mod) + (ret >> 61);
        ret     = (ret & mod) + (ret >> 61);
        return ret - 1;
    }
    ull gethash(int l, int r)
    {
        return sub(h[r], mul(h[l - 1], p[r - l + 1]));
    }
    ull gethash()
    {
        return h[n];
    }
};
vui Phash::p{ 1 };