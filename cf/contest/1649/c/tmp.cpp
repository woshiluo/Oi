// Problem: C. Weird Sum
// Contest: Codeforces - Codeforces Round #775 (Div. 2, based on Moscow Open Olympiad in Informatics)
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Lately, I've been hearing the cries of the angels when I close my eyes.
// 
// Copied from https://codeforces.com/contest/1649/submission/148566293, just for testing.

#include <bits/stdc++.h>

template <class T>
inline void read(T &x) {
    x = 0;
    int f = 0;
    char ch = getchar();
    while (!isdigit(ch))    { f |= ch == '-'; ch = getchar(); }
    while (isdigit(ch))     { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    x = f ? -x : x;
    return ;
}

typedef unsigned long long uLL;
typedef long long LL;

struct Node {
    int x, y;
};

std::vector<Node> c[100010];
LL tx[100010], ty[100010], cx[100010], cy[100010];
LL ans;
int a[1010][1010];
int n, m;

void modify(LL *t, int x, LL d) {
    for (; x <= 100000; x += x & -x)    t[x] += d;
    return ;
}

LL query(LL *t, int x) {
    LL s = 0;
    for (; x; x -= x & -x)    s += t[x];
    return s;
}

int main() {
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            read(a[i][j]);
            c[a[i][j]].push_back((Node){i, j});
        }
    }
    for (int i = 1; i <= 100000; ++i) {
        for (auto j : c[i]) {
            modify(tx, j.x, j.x);
            modify(cx, j.x, 1);
            modify(ty, j.y, j.y);
            modify(cy, j.y, 1);
        }
        LL res = 0;
        for (auto j : c[i]) {
            res += query(cx, j.x - 1) * j.x - query(tx, j.x - 1);
            res += query(tx, 100000) - query(tx, j.x) - (query(cx, 100000) - query(cx, j.x)) * j.x;
            res += query(cy, j.y - 1) * j.y - query(ty, j.y - 1);
            res += query(ty, 100000) - query(ty, j.y) - (query(cy, 100000) - query(cy, j.y)) * j.y; 
        }
        for (auto j : c[i]) {
            modify(tx, j.x, -j.x);
            modify(cx, j.x, -1);
            modify(ty, j.y, -j.y);
            modify(cy, j.y, -1);
        }
        ans += res;
    }
    printf("%lld\n", ans / 2);
    return 0;
}
