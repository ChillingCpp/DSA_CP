using ll = long long;
const ll MOD = 1e9+7; // đổi nếu cần, hoặc bỏ nếu không dùng modulo

vector<vector<ll>> multiply(const vector<vector<ll>>& A,
                            const vector<vector<ll>>& B) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size(); // = A[0].size()

    vector<vector<ll>> C(n, vector<ll>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < p; k++) {
            if (A[i][k] == 0) continue; // tối ưu nhỏ
            for (int j = 0; j < m; j++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}
