T dfs(int pos, bool tight, bool started, State s) {
    if (pos == n) return base(started, s);

    if (!tight && vis[pos][started][s]) return memo[pos][started][s];

    int lim = tight ? dig[pos] : 9;
    T ans = identity();

    for (int d = 0; d <= lim; ++d) {
        bool nstarted = started || (d != 0);
        State ns = next_state(s, d, nstarted);
        if (!valid_prefix(ns, nstarted)) continue;

        bool ntight = tight && (d == dig[pos]);
        T child = dfs(pos + 1, ntight, nstarted, ns);
        ans = combine(ans, lift(child, d, pos));
    }

    if (!tight) {
        vis[pos][started][s] = true;
        memo[pos][started][s] = ans;
    }
    return ans;
}

T solve(long long X) {
    if (X < 0) return identity_zero_query();
    dig = to_digits(X);
    n = dig.size();
    clear_memo();
    return dfs(0, true, false, init_state());
}
