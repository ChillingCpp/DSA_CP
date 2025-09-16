

// recursively divide the array into 2 or 3 parts, often 2 parts, run in Logarit time complexity

/// divide and conquer count inversion : 
// merge sort
int cnt = 0;
void merge(int l, int m, int r)
{
    // perform insertion sort to merge a[l..m] and a[m+1...r] to a[l...r]
    vi tmp1, tmp2;
    for (int i = l; i <= m; ++i)
        tmp1.push_back(a[i]);
    for (int i = m+1; i <= r; ++i)
        tmp2.push_back(a[i]);

    int k = l;
    int i = 0, j = 0;
    int n1=  tmp1.size();
    int n2 = tmp2.size();
    while (i < n1 && j < n2){

        if (tmp1[i] <= tmp2[j])
            a[k++] = tmp1[i++];
        else
        {
            cnt += (n1 - i);
            a[k++] = tmp2[j++];
        }
    }
    while (i < n1) a[k++] = tmp1[i++];
    while (j < n2) a[k++] = tmp2[j++];
}
void mergesort(int l, int r, vector<int> &a)
{
    if (l > r) return; // cannot divide;
    int mid = l + (r - l) /2;
    mergesort(l, mid, a);
    mergesort(mid+1, r, a);
    merge(l, m, r, a);
}