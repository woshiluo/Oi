#include <cstdio>
#include <algorithm>
typedef long long ll;
const int N = 10000007;
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}
inline ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

struct edge {
    int s, t;
    ll l;
    edge():s(0), t(0), l(0) {}
    edge(int s, int t, ll l):s(s), t(t), l(l) {}
    bool operator<(const edge& b) {
        return l < b.l;
    }
}e[N];

int fa[N], e_tot;
int find(int x) {
    return x == fa[x] ? x : x = find(fa[x]);
}
void merge(int a, int b) {
    fa[find(a)] = find(b);
}

ll kruskal(int n) {
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    ll ret = 0;
    std::sort(e + 1, e + e_tot + 1);
    for (int i = 1, left = n - 1; left && i <= e_tot; ++i) {
        if (find(e[i].s) == find(e[i].t)) {
            continue;
        }
//		printf( "%d %d %lld\n", e[i].s, e[i].t, e[i].l );
        ret += e[i].l;
        merge(e[i].s, e[i].t);
        --left;
    }
    return ret;
}

int main() {
	freopen( "tmp.in", "r", stdin );
	freopen( "tmp.out", "w", stdout );

    int l, r;
    scanf("%d%d", &l, &r);
    for (int i = l; i <= r; ++i) {
        for (int j = i + 1; j <= r; ++j) {
            e[++e_tot] = edge(i - l + 1, j - l + 1, lcm(i, j));
        }
    }
    printf("%lld", kruskal(r - l + 1));
    return 0;
}
