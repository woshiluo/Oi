/*
Author: Zcus
Blog: https://cnblogs.com/zcus
*/

#include <bits/stdc++.h>
using namespace std;

template <class T>
inline T read() {
    T s = 0, w = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        s = s * 10 + (c ^ 48);
        c = getchar();
    }
    return s * w;
}

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define ri read<int>
#define pii pair<int, int>
#define rl read<long long>
#define debug(x) cout << #x << " = " << x << endl
#define fr(i, x, y) for (int i = x; i <= y; i++)
#define rp(i, x, y) for (int i = x; i >= y; i--)
#define ddbug(x, y) cout << #x << " = " << x << " " << #y << " = " << y << "\n"
#define file(FILE_NAME) freopen(FILE_NAME ".in", "r", stdin), freopen(FILE_NAME ".out", "w", stdout)
#define filein(FILE_NAME) freopen(FILE_NAME ".in", "r", stdin);
#define fileout(FILE_NAME) freopen(FILE_NAME ".out", "w", stdout);

template <class T>
inline bool chkmax(T& x, const T& y) {
    return x < y ? x = y, true : false;
}
template <class T>
inline bool chkmin(T& x, const T& y) {
    return x > y ? x = y, true : false;
}

const int maxn = 6e5 + 50;
const int maxm = 6e5 + 50;

int du[maxn], root, ans;
vector<int> G[maxn];

int x0[maxn], x1[maxn], n;
void dfs(int x, int fa) {
    if (G[x].size() == 1) {
        x1[x] = 1;
        x0[x] = 0;  // 0 bixu 1 bubixu
        return;
    }
    int cnt = 0;
    for (int v : G[x]) {
        if (v == fa)
            continue;
        dfs(v, x);
        cnt++;
        x0[x] += x0[v];
        x1[x] += x1[v];
    }
    if (cnt <= 1)
        return;
    if (x == root) {
        if ((x0[x] + x1[x]) % 2 == 0) {
            ans = ans + (x0[x] + x1[x]) / 2;
            return;
        } else {
            ans = ans + (x0[x] + x1[x]) / 2;
            if (x1[x] == 0)
                ans++;
            return;
        }
        return;
    }
    if ((x0[x] + x1[x]) % 2 == 1) {
        if (x1[x])
            ans = ans + (x0[x] + x1[x] - 1) / 2, x1[x] = 1, x0[x] = 0;
        else if (x0[x])
            ans = ans + (x0[x] + x1[x] - 1) / 2, x1[x] = 0, x0[x] = 1;
    } else {
        if (x1[x] == 0) {
            ans = ans + (x0[x] + x1[x]) / 2, x1[x] = 0;
            x0[x] = 0;
        } else {
            ans = ans + (x0[x] + x1[x] - 1) / 2;
            x1[x] = 0;
            x0[x] = 1;
        }
    }
}

int main() {
    // file("tree");
    n = ri();
    fr(i, 1, n - 1) {
        int x = ri(), y = ri();
        du[x]++;
        du[y]++;
        G[x].pb(y);
        G[y].pb(x);
    }
    fr(i, 1, n) if (du[i] != 1) {
        root = i;
        break;
    }
    dfs(root, 0);
    printf("%d\n", ans);
    return 0;
}
