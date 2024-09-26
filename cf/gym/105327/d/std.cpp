#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define sq(x) (x)*(x)
template<class T, class U> inline void chmin(T& a, U b) { if (a > b) a = b; }
template<class T, class U> inline void chmax(T& a, U b) { if (a < b) a = b; }
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef long double ld;
typedef __int128 i128;

template<int mod = (int)1e9 + 7>
struct mint {
    int x;
    mint() : x(0) {}
    mint(ll _x) { _x %= mod; if (_x < 0) _x += mod; x = _x; }
    mint& operator += (mint o) { x += o.x; if (x >= mod) x -= mod; return *this; }
    mint& operator -= (mint o) { x -= o.x; if (x < 0) x += mod; return *this; }
    mint& operator *= (mint o) { x = (ll)x * o.x % mod; return *this; }
    mint& operator /= (mint o) {
        ll a = o.x, b = mod, u = 1, v = 0;
        while (b > 0) {
            ll t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        if (u < 0) u += mod;
        return *this *= u;
    }
    mint& operator ^= (ll e) { 
        ll b = x; x = 1;
        while (e > 0) {
            if (e & 1ll) x = x * b % mod;
            b = b * b % mod, e >>= 1ll;
        }
        return *this;
    }
    mint operator + (mint o) const { return mint(*this) += o; }
    mint operator - (mint o) const { return mint(*this) -= o; }
    mint operator * (mint o) const { return mint(*this) *= o; }
    mint operator / (mint o) const { return mint(*this) /= o; }
    mint operator ^ (ll o) const { return mint(*this) ^= o; }
    bool operator < (mint o) const { return x < o.x; }
    bool operator == (mint o) const { return x == o.x; }
    bool operator != (mint o) const { return x != o.x; }
};

template <typename U, int mod>
U& operator >> (U& is, mint<mod>& number) {
    ll x;
    is >> x;
    number = mint(x);
    return is;
}

using Int = mint<(int)1e9 + 7>;

template<typename T, int N> struct matrix {
    array<array<T, N>, N> a{};
    matrix operator * (const matrix &o) const {
        matrix ans;
        rep(i, 0, N) rep(j, 0, N) rep(k, 0, N)
            ans.a[i][j] += a[i][k] * o.a[k][j];
        return ans;
    }
    matrix operator ^ (ll e) const {
        matrix ans, self(*this);
        rep(i, 0, N) ans.a[i][i] = 1;
        while (e > 0) {
            if (e & 1) ans = ans * self;
            self = self * self;
            e >>= 1;
        }
        return ans;
    }
    vector<T> operator * (const vector<T> &o) const {
        vector<T> ans(N);
        rep(i, 0, N) rep(j, 0, N) ans[i] += a[i][j] * o[j];
        return ans;
    }
    array<T, N>& operator[](int i) {
        return a[i];
    }
};

const int N = 100, LG = 61;
using M = matrix<Int, N>;

int main() {
	freopen( "d.in", "r", stdin );
	freopen( "d.ans", "w", stdout );
    cin.tie(0)->sync_with_stdio(0);

    ll n, m; cin >> n >> m;

    vector<M> pot(LG);
    rep(i, 0, LG) {
        rep(j, 1, N) pot[i][j][j - 1] = 1;
    }

    rep(i, 0, m) {
        int a, b; cin >> a >> b;
        rep(j, b, LG) pot[j][0][a - 1] += 1;
    }

    vector<M> pref(LG);
    rep(i, 0, N) pref[0][i][i] = 1;

    rep(i, 1, LG) {
        pref[i] = pref[i - 1] * pot[i - 1] * pref[i - 1];
    }

    M magic;
    rep(i, 0, N) magic[i][i] = 1;

    while (n > 0) {
        ll msb = 63 - __builtin_clzll(n & -n);
        magic = magic * pot[msb] * pref[msb];
        n -= n & -n;
    }

    vector<Int> ans(N);
    ans[0] = 1;
    ans = magic * ans;

    cout << ans[0].x << endl;
}
