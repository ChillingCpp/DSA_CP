int n = 1e5;
vector<int> mode(n+1, 0); // 0 : unvisted, 1: visited and still in dfs tree, 2 : completed visited, will never untouched.
vector<vector<int>> a;
vector<int> ans;
bool dfs(int u)
{
    mode[u] = 1;
    for (auto& v: a[u]){
        if (mode[v] == 1) 
            return false;
        if (!mode[v] && !dfs(v))
            return false;
    }
    mode[u] = 2;
    ans.push_back(u);
    return true;
}

// how to use : //
bool cycle = 0;
for (int i = 1; i <= n; ++i)
    if (!mode[i])
        if (!dfs(i)){
            cycle = 1;
            break;
        }
}
if (cycle){
    cout << "Cycle detected, abort\n":
    return 0;
}
reverse(ans.begin(), ans.end());
