#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '.') a[i][j] = 1;
            else a[i][j] = 0;
        }
    }

    auto l = a, r = a;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (l[i][j]) {
                l[i][j] += l[i][j - 1];
            }
        }
        for (int j = m - 2; j >= 0; j--) {
            if (r[i][j]) {
                r[i][j] += r[i][j + 1];
            }
        }
    }

    auto u = a, d = a;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (u[i][j]) {
                u[i][j] += u[i - 1][j];
            }
        }
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            if (d[i][j]) {
                d[i][j] += d[i + 1][j];
            }
        }
    }

    int ans = 0;
    vector<int> rows;

    for (int i = 0; i < n; i++) {
        int mx = 0;
        vector<pair<int, int>> seg;
        for (int j = 0; j < m; j++) {
            if (!a[i][j]) {
                continue;
            }
            
            int L = j - l[i][j] + 1;
            int R = j + r[i][j] - 1;
            mx = max(mx, R - L + 1);
            seg.emplace_back(L, R);
        }
        seg.resize(unique(seg.begin(), seg.end()) - seg.begin());
        if (seg.size() == 0) {
            
        } else if (seg.size() == 1) {
            ans = max(ans, seg[0].second - seg[0].first + 1);
        } else {
            sort(seg.begin(), seg.end(), [&](auto x, auto y) {
                return x.second - x.first > y.second - y.first;
            });
            ans = max(ans, seg[0].second - seg[0].first + 1 + seg[1].second - seg[1].first + 1);
        }
        rows.push_back(mx);
    }
    auto pref = rows;
    auto suf = rows;
    for (int i = 1; i < n; i++) {
        pref[i] = max(pref[i - 1], pref[i]);
    }
    for (int i = n - 2; i >= 0; i--) {
        suf[i] = max(suf[i], suf[i + 1]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!a[i][j]) continue;
            int U = i - u[i][j] + 1;
            int D = i + d[i][j] - 1;
            int mx = max(U ? pref[U - 1] : 0, (D + 1 < n) ? suf[D + 1] : 0);
            ans = max(ans, mx + D - U + 1);
        }
    }

    rows.push_back(0);
    sort(rows.begin(), rows.end(), greater<int>());
    ans = max(ans, rows[0] + rows[1]);


    vector<int> cols;
    for (int j = 0; j < m; j++) {
        int mx = 0;
        vector<pair<int, int>> seg;
        for (int i = 0; i < n; i++) {
            if (!a[i][j]) {
                continue;
            }
            int U = i - u[i][j] + 1;
            int D = i + d[i][j] - 1;
            mx = max(mx, D - U + 1);
            seg.emplace_back(U, D);
        }
        seg.resize(unique(seg.begin(), seg.end()) - seg.begin());
        if (seg.size() == 0) {

        } else if (seg.size() == 1) {
            ans = max(ans, seg[0].second - seg[0].first + 1);
        } else {
            sort(seg.begin(), seg.end(), [&](auto x, auto y) {
                return x.second - x.first > y.second - y.first;
            });
            ans = max(ans, seg[0].second - seg[0].first + 1 + seg[1].second - seg[1].first + 1);
        }
        cols.push_back(mx);
    }
    pref = cols;
    suf = cols;
    for (int j = 1; j < m; j++) {
        pref[j] = max(pref[j], pref[j - 1]);
    }
    for (int j = m - 2; j >= 0; j--) {
        suf[j] = max(suf[j], suf[j + 1]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!a[i][j]) {
                continue;
            }
            int L = j - l[i][j] + 1;
            int R = j + r[i][j] - 1;
            int mx = max(L ? pref[L - 1] : 0, (R + 1 < m) ? suf[R + 1] : 0);
            ans = max(ans, mx + R - L + 1);
        }
    }

    cols.push_back(0);
    sort(cols.begin(), cols.end(), greater<int>());
    ans = max(ans, cols[0] + cols[1]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!a[i][j]) {
                continue;
            }
            int U = i - u[i][j] + 1;
            int D = i + d[i][j] - 1;
            int L = j - l[i][j] + 1;
            int R = j + r[i][j] - 1;

            ans = max(ans, D - U + 1 + R - j);
            ans = max(ans, D - U + 1 + j - L);
            ans = max(ans, R - L + 1 + D - i);
            ans = max(ans, R - L + 1 + i - U);
        }
    }
    cout << ans << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}