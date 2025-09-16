

vector<int> a;
vector<int> idx;
iota(idx.begin, idx.end(), 0);
sort(idx.begin(), idx.end(), [&}(int&p, int&q){return a[p] < a[q]; });

/// examples : given N and K, your perform 1 operations : choose the interval size K and set all minimum element in it to -1, 
/// all element mark as -1 is unactive, you cannot process it more, find the minimum number of operations to make all element unactive

int minop = 0;
int cur = idx[0];
for (int i = 1; i < n; ++i)
{
    if (a[idx[i]] > a[cur] || (idx[i] - cur +1) > K){
        cur = idx[i];
        minop++;
    }
}
