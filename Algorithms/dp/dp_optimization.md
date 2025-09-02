
[Learning DP optimization](https://codeforces.com/blog/entry/)

[Some practical problems](https://codeforces.com/blog/entry/47932)


| Name                        | Original Recurrence                                   | Sufficient Condition of Applicability       | Original Complexity | Optimized Complexity | Links    |
|-----------------------------|-------------------------------------------------------|--------------------------------------------|---------------------|----------------------|----------|
| Convex Hull Optimization1   | $dp[i] = \min_{j<i} \{ dp[j] + b[j] \cdot a[i] \}$     | $b[j] \geq b[j+1]$<br>optionally $a[i] \leq a[i+1]$ | $O(n^2)$            | $O(n)$               | [1](https://web.archive.org/web/20181030143808/http://wcipeg.com/wiki/Convex_hull_trick) [2](https://cp-algorithms.com/geometry/convex_hull_trick.html) [3](https://codeforces.com/blog/entry/63823) [p1](https://codeforces.com/contest/319/problem/C) |
| Convex Hull Optimization2   | $dp[i][j] = \min_{k<j} \{ dp[i-1][k] + b[k] \cdot a[j] \}$ | $b[k] \geq b[k+1]$<br>optionally $a[j] \leq a[j+1]$ | $O(kn^2)$           | $O(kn)$              | [1](http://apps.topcoder.com/forums/?module=Thread&threadID=608334&start=0&mc=14#1120736) [p1](http://www.spoj.com/problems/NKLEAVES/) [p2](https://codeforces.com/contest/311/problem/B)  |
| Divide and Conquer Optimization | $dp[i][j] = \min_{k<j} \{ dp[i-1][k] + C[k][j] \}$   | $A[i][j] \leq A[i][j+1]$                    | $O(kn^2)$           | $O(kn \log n)$       | [1](https://codeforces.com/blog/entry/8192) [p1](https://codeforces.com/contest/321/problem/E)     |
| Knuth Optimization          | $dp[i][j] = \min_{i<k<j} \{ dp[i][k] + dp[k][j] + C[i][j] \}$ | $A[i,j-1] \leq A[i,j] \leq A[i+1,j]$        | $O(n^3)$            | $O(n^2)$             | [1](http://apps.topcoder.com/forums/?module=Message&messageID=823126) [2](http://apps.topcoder.com/forums/?module=Thread&threadID=697369&start=0&mc=22#1327577) [p1](http://www.spoj.com/problems/BRKSTRNG/)   |
