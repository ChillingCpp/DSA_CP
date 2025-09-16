vi sliding(vector<int>& a, int k, function<ll(ll, ll)> cmp)
{
    int n = a.size();
    deque<int>dq;
    vi ans;
    for (int i = 0; i < k; ++i){

        while (dq.size() && cmp(a[dq.back()], a[i])) dq.pop_back();
        dq.push_back(i);
    }
    ans.push_back(a[dq.front()]);
    for (int i = k; i < n; ++i)
    {
        while (dq.size() && dq.front() < i - k + 1) dq.pop_front();
        while (dq.size() && cmp(a[dq.back()], a[i])) dq.pop_back();
        ans.push_back(a[dq.front()]);
        dq.push_back(i);
    }
    return ans;
}
