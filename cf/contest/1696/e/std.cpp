/********************************************************
> File Name: e.cpp
> Author: 15owzLy1
> Mail: I5owzLy1@outlook.com 
> Created Time: 2022/6/26 0:03:36
 *******************************************************/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
template<typename T>inline void chk_min(T &_, T __) { _ = _ < __ ? _ : __; }
template<typename T>inline void chk_max(T &_, T __) { _ = _ > __ ? _ : __; }
int in() {
    int x = 0; char c = getchar(); bool f = 0;
    while (c < '0' || c > '9')
        f |= c == '-', c = getchar();
    while (c >= '0' && c <= '9')
        x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? -x : x;
}
long long lin() {
    long long x = 0; char c = getchar(); bool f = 0;
    while (c < '0' || c > '9')
        f |= c == '-', c = getchar();
    while (c >= '0' && c <= '9')
        x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? -x : x;
}

const int N = 4e5 + 5, mod = 1e9 + 7;

int a[N];
int fac[N << 1], inv[N << 1];

int qpow(int base, int b, int ret = 1) {
    for (; b; b >>= 1, base = 1ll * base * base % mod)
        if (b & 1)
            ret = 1ll * ret * base % mod;
    return ret;
}

void prep() {
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= N; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[N] = qpow(fac[N], mod - 2);
    for (int i = N - 1; i; --i)
        inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
}

int C(int n, int m) {
    return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    //freopen("in", "r", stdin);
    prep();
    int n = in();
    for (int i = 0; i <= n; ++i)
        a[i] = in();
    long long ans = 0;
    int last = -1;
    for (int i = 0; i <= n; ++i) {
        if (a[i] > a[i + 1]) {
            //printf("%d\n", C(i + a[i] + 1, i + 1) - 1);
            (ans += C(i + a[i] + 1, i + 1) - 1 + mod) %= mod;
            if (last != -1) {
                ans -= C(last + a[i] + 1, last + 1) - 1;
                ans += mod;
                ans %= mod;
            }
            last = i;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
