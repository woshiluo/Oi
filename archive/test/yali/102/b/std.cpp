// Code By CXY07 - It's My Fiesta.
#include <bits/stdc++.h>
using namespace std;

//#define FILE
#define int long long
#define randint(l, r) (rand() % ((r) - (l) + 1) + (l))
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define popc(x) __builtin_popcount(x)
#define inv(x) qpow((x), mod - 2)
#define lowbit(x) ((x) & (-(x)))
#define ull unsigned long long
#define pii pair<int, int>
#define LL long long
#define mp make_pair
#define pb emplace_back
#define scd second
#define vec vector
#define fst first
#define endl '\n'

const int MAXN = (1 << 19) + 10;
const int INF = 2e9;
const double eps = 1e-6;
const double PI = acos(-1);
// const int mod = 1e9 + 7;
// const int mod = 998244353;
// const int G = 3;
// const int base = 131;

int n = (1 << 19), V, k;
int a[4][MAXN], p[110];
vec<int> G[4][(1 << 19) + 10];
vec<int> opt;
unordered_map<int, pii> ok;
mt19937 rnd(5224999);

template <typename T>
inline bool read(T &a) {
    a = 0;
    char c = getchar();
    int f = 1;
    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        a = a * 10 + (c ^ 48);
        c = getchar();
    }
    return a *= f, true;
}

template <typename A, typename... B>
inline bool read(A &x, B &... y) {
    return read(x) && read(y...);
}

namespace naive {
void solve() {
    for (int i = 0; i <= 2; ++i)
        for (int j = 1; j <= n; ++j)
            if (!a[i][j]) {
                printf("%lld ", j);
                break;
            }
    for (int j = 1; j <= n; ++j)
        if (a[3][j] == V) {
            printf("%lld\n", j);
            break;
        }
}
}  // namespace naive

void calc() {
    int lim = 17;
    opt.clear();
    ok.clear();
    for (int i = 1; i <= k; ++i) p[i] = i - 1;
    shuffle(p + 1, p + k + 1, rnd);
    for (int s = 0; s <= 3; ++s) {
        for (int i = 1, cur; i <= n; ++i) {
            cur = 0;
            for (int j = 1; j <= lim; ++j) cur |= ((a[s][i] >> p[j]) & 1) << (j - 1);
            opt.pb(cur);
            G[s][cur].pb(i);
        }
    }
    sort(opt.begin(), opt.end());
    opt.erase(unique(opt.begin(), opt.end()), opt.end());
    for (auto x : opt)
        for (auto i : G[0][x])
            for (auto j : G[1][x]) ok[a[0][i] ^ a[1][j]] = mp(i, j);
    for (auto x : opt)
        for (auto i : G[2][x])
            for (auto j : G[3][x])
                if (ok.count(a[2][i] ^ a[3][j])) {
                    int v = a[2][i] ^ a[3][j];
                    printf("%lld %lld %lld %lld", ok[v].fst, ok[v].scd, i, j);
                    exit(0);
                }
    for (auto x : opt) G[0][x].clear(), G[1][x].clear(), G[2][x].clear(), G[3][x].clear();
}

signed main() {
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
    read(k), read(V);
    for (int i = 0; i <= 3; ++i)
        for (int j = 1; j <= n; ++j) read(a[i][j]);
    if (k <= 12)
        return naive::solve(), 0;
    for (int i = 1; i <= n; ++i) a[0][i] ^= V;
    V = 0;
    while (1) calc();
    return 0;
}

