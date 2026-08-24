
/// range query point update trong log^2(n). cấu trúc này hoạt động hiệu quả khi hệ trục tọa độ thưa, chỉ có N điểm ( thường là 1e5 ) 
// nhưng cần hệ trục khoảng 1e5  * 1e5 để chứa hết các điểm đó.

int get_id(const vector<int>& arr, int v, bool upper = false) {
    if (upper) return upper_bound(arr.begin(), arr.end(), v) - arr.begin();
    return lower_bound(arr.begin(), arr.end(), v) - arr.begin();
}

struct Seg1D {
    int n;
    vector<int> ys;       // tọa độ y sau nén
    vector<ll> t;  // cây 1D

    void build(const vector<int>& coords) {
        ys = coords;
        n = ys.size();
        t.assign(2 * n, 0);
    }

    void update(int y, ll val) {
        int p = get_id(ys, y);
        for (p += n; p > 0; p >>= 1) t[p] += val;
    }

    ll query(int y1, int y2) {
        int l = get_id(ys, y1);
        int r = get_id(ys, y2, true); // upper_bound
        ll res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};

struct Seg2D {
    int n;
    vector<int> xs; 
    vector<Seg1D> st;       

    void build(vector<pair<int,int>>& pts) {
        // nén tọa độ x
        xs.clear();
        for (auto& p : pts) xs.push_back(p.first);
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        n = xs.size();

        st.assign(2 * n, {});
        vector<vector<int>> ys(2 * n);

        /// trong đoạn [xL...xR] có bao nhiêu tọa độ Y unique trong đây
        for (auto& p : pts) {
            int pos = get_id(xs, p.first);
            for (pos += n; pos > 0; pos >>= 1) ys[pos].push_back(p.second);
        }

        // build Seg1D tại từng node
        for (int i = 0; i < 2 * n; i++) {
            if (ys[i].empty()) continue;
            sort(ys[i].begin(), ys[i].end());
            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
            st[i].build(ys[i]);
            
        }
    }

    void update(int x, int y, ll val) {
        int pos = get_id(xs, x);
        for (pos += n; pos > 0; pos >>= 1) st[pos].update(y, val);
    }

    ll query(int x1, int y1, int x2, int y2) {
        int L = get_id(xs, x1);
        int R = get_id(xs, x2, true); 
        ll res = 0;
        for (L += n, R += n; L < R; L >>= 1, R >>= 1) {
            if (L & 1) res += st[L++].query(y1, y2);
            if (R & 1) res += st[--R].query(y1, y2);
        }
        return res;
    }
};
