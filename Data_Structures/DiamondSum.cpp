
for (int x = 1; x <= n; ++x) {
    for (int y = 1; y <= m; ++y) {
        int u = x + y;
        int v = x - y + m + 1; // offset
        b[u][v] += a[x][y];
    }
}

vector<vector<int>> pref(n + m + 1, vector<int>(n + m + 1));
for (int i = 2; i <= n + m; ++i)
    for (int j = 2; j <= n + m; ++j)
        ....

//// query tâm (x0, y0) ban đầu với bán kính mahattan = k
long long query_diamond(int x0, int y0, int k) {
    // mục tiêu : (x0, y0) -> (u1, v1) và (u2, v2)
    int u1 = max(2, x0 + y0 - k);
    int u2 = min(n + m, x0 + y0 + k);
    int v1 = max(2, x0 - y0 - k + m + 1);
    int v2 = min(n + m, x0 - y0 + k + m + 1);

    if (u1 > u2 || v1 > v2) return 0;

    return pref[u2][v2] - pref[u1 - 1][v2] - pref[u2][v1 - 1] + pref[u1 - 1][v1 - 1];
}
