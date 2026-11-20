
Sparse_table s(arr);
int val = 0;
int lo = l;
while (l <= r){
    int m = (l + r) / 2;
    if (check(s, lo, m, val))
        l = m+ 1;
    else r = m-1;
}
