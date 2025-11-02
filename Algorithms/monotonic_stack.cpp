
// Comparator has 2 parameter and return a boolean
template<typename T, typename Comparator>
vector<int> nextst(vector<T>& a, Comparator cmp)
{
    int         n = a.size();
    stack<int>  st;
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; --i)
    {
        while (st.size() && cmp(a[st.top()], a[i]))
            st.pop();
        ans[i] = (st.size()) ? st.top() : -1;
        st.push(i);
    }
    return ans;
}

template<typename T, typename Comparator>
vector<int> prevst(vector<T>& a, Comparator cmp)
{
    int         n = a.size();
    stack<int>  st;
    vector<int> ans(n);
    for (int i = 0; i < n; ++i)
    {
        while (st.size() && cmp(a[st.top()], a[i]))
            st.pop();
        ans[i] = (st.size() ? st.top() : n);
        st.push(i);
    }
    return ans;
}
// now l[i] and r[i] is where the a[i] contribute as comparator result element, interval have n *
// (n+1) /2 subinterval;
template<typename T, typename Comparator>
pair<vector<int>, vector<int>> boundary(vector<T>& a, Comparator cmp)
{
    return { prevst(a, cmp), nextst(a, cmp) };
}
