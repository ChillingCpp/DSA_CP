/// binary search searching elements :
/// requires : sorted array
upper_bound(x) : leftmost smallest element in array > x
lower_bound(x) : leftmost largest element in array >= x








/// Binary search on answers
/// requires : sorted array or check function is monotone
bool check(int mid)
{
  
}
ll low = 0, high = 1e10;
while (low <= high)
{
    ll mid = (low + high) / 2;
    if (check(mid))
        high = mid - 1;
    else
        low = mid + 1;
}
cout << low << '\n';
