/// ternary search works in log1.5(n), little slower than binary search
/// ternary search works with 1-extrema functions ( min or max ), monotone can work with but use binary search instead 

ll f(ll v)
{
}
ll ternary()
{
    ll low = 0, high = 1e18;
    while (high - low >= 3)
    {
        ll m1 = low + (high - low) / 3;
        ll m2 = high - (high - low) / 3;
        // finding max
        if (f(m1) < f(m2))
            low = m1;
        else
            high = m2;

        // finding min
        if (f(m1) > f(m2))
            high = m2;
        else
            low = m1;
    }
    ll best = low;
    for (ll i = low + 1; i <= high; ++i)
        if (f(best) < f(i))
            best = i;
    return best;
}

int mlog(double val)
{
    return (int) (log(val) / log(1.5)) + 1;
}
double f(double v)
{
}
double ternary()
{
    double low = 0, high = 1e18, eps = 1e-6;
    int    iter = mlog((high - low) / eps);
    while (high - low >= 3)
    {
        double m1 = low + (high - low) / 3;
        double m2 = high - (high - low) / 3;
        // finding max
        if (f(m1) < f(m2))
            low = m1;
        else
            high = m2;

        // finding min
        if (f(m1) > f(m2))
            high = m2;
        else
            low = m1;
    }
    return (low + high) / 2;
}
