/// binary search searching elements :
/// requires : sorted array
upper_bound(x) : leftmost smallest element in array > x
lower_bound(x) : leftmost largest element in array >= x

/// Binary search on answers, integer range
/// requires : sorted array or check function is monotone
bool check(int mid)
{
  
}
ll low = 0, high = 1e10;
while (low <= high)
{
    ll mid = (low + high) / 2;
    if (check(mid))
        high = mid - 1; // or low = mid + 1
    else
        low = mid + 1; // or high = mid -1;
}
cout << low << '\n';

/// Binary search on answers, real value range [L, R]
/// requires : sorted array or check function is monotone
bool check(double mid)
{
  
}
double low = 0, high = 1e10, eps = 1e-7;
int iter = int(log2((r - l)/ eps))+ 3;
while (iter--)
{
    ll mid = (low + high) / 2;
    if (check(mid))
        low = mid; // or high = mid
    else
        high = mid; // or low = mid;
}
cout << (low + high) /2 << '\n';
