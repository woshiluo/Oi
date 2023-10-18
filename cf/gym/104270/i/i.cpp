#include <bits/stdc++.h>

using namespace std;


void solve() {

    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) 
        cin >> a[i];
    vector<array<long long, 3>> aa;
    for (int i = 0; i < n; i++)
        aa.emplace_back(array<long long, 3>{a[i], i, 0});
        
    for (int i = 0; i + 1 < n; i++)
        aa.emplace_back(array<long long, 3>{a[i] + a[i + 1], i, 1});
       
    sort(aa.begin(), aa.end());
    
    
    vector<array<array<int, 2>, 2>> t(n * 2);
    for (int i = 0; i < n; i++)
        t[i + n][1][0] = 1;
    auto update = [&](int x) {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++) {
                t[x][i][j] = 0;
                for (int k = 0; k < 2; k++)
                    t[x][i][j] |= t[x * 2][i][k] & t[x * 2 + 1][k][j];
            }
    };
    
    
    auto upd = [&](int x, int c, bool k) {
        x += n;
        t[x][0][c] = k;
        while (x >>= 1)
            update(x);
    };
    int j = -1;
    long long mn = 2e18 + 1;
    for (int i = 0; i < n * 2 - 1; i++) {
        auto [v, x, c] = aa[i];
        upd(x, c, 1);
        while (j + 1 < n * 2 - 1 && t[1][0][0]) {
            auto [v2, x2, c2] = aa[j + 1];
            upd(x2, c2, 0);
            j += 1;
        }
        if (j >= 0)
        	mn = min(mn, v - aa[j][0]);
    }
    
    cout << mn << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        solve();
        
    return 0;
}

/*

1
4
1000000000 1000000000 -1000000000 -1000000000

*/
