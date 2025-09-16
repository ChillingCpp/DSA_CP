
void nextgreater(vector<int> &a)
{

    int n = a.size();
    stack<int> st;
    vector<int> ans(n);
    for (int i =n-1 ;i >=0; --i)
    {
        while (st.size() && a[st.top()] <= a[i])st.pop();
        ans[i] = (st.size()) ? a[st.top()] : -1;
        st.push(i);
    }
}

void boundarymax(vector<int> &a)
{
    int n = a.size();
    stack<int> st;
    vector<int> ans(n), l(n), r(n);
    for (int i =n-1 ;i >=0; --i)
    {
        while (st.size() && a[st.top()] <= a[i])st.pop();
        r[i] = (st.size() ? st.top() : n);
        st.push(i);

    }
    st= stack<int>();
    for (int i =0  ;i < n;++i)
    {
        while (st.size() && a[st.top()] <= a[i])st.pop();
        l[i] = (st.size() ? st.top() : -1); // outside
        st.push(i);
    }

    // now l[i] and r[i] is where the a[i] contribute as max element, interval have n * (n+1) /2 subinterval;
}
