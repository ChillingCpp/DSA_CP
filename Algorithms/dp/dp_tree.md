
dp on tree is basically is dfs, either update preorder ( calc child based on parent ) or postorder ( calc parent based on child )

normally we only have dp[u] mean value in node u, we can have more state to the dp, dp[u][state] mean value of u when its in this state, and more ...


dp rerooting is a technique when we need to calc all nodes in O(n), first dfs start at 1
start another dfs, create old value then calculate new value dp[u], dp[v] of the current node u and adjacent node V then in preorder, 
reassign value dp[u], dp[v] to old value after dfs ( postorder )

then we have dp[i] is the answer for the node i


dp knapsack on tree



dp tree smaller to larger merge optimization
