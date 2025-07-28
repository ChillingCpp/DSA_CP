

// recursively divide the array into 2 or 3 parts, often 2 parts, run in Logarit time complexity

// merge sort
void merge(int l, int m, int r)
{
    // perform insertion sort to merge a[l..m] and a[m+1...r] to a[l...r]
}
void mergesort(int l, int r, vector<int> &a)
{
    if (l > r) return; // cannot divide;
    int mid = l + (r - l) /2;
    mergesort(l, mid, a);
    mergesort(mid+1, r, a);
    merge(l, m, r, a);
}