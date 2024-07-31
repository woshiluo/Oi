//Mercy
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 7, MOD = 998244353;
int n, q;
vector<int> e[N];
ll f[N], ivf[N];
int par[N], sz[N], ch[N], top[N];
int ind, dfx[N], rdfx[N];

ll qpow(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}

ll getInv(ll x) {
    return qpow(x, MOD - 2);
}

void init() {
    f[0] = 1;
    for (int i = 1; i < N; i++) f[i] = f[i - 1] * i % MOD;
    ivf[N - 1] = getInv(f[N - 1]);
    for (int i = N - 2; i >= 0; i--) ivf[i] = ivf[i + 1] * (i + 1) % MOD;
}

void dfs0(int now) {
    sz[now] = 1;
    for (auto to: e[now]) {
        dfs0(to);
        sz[now] += sz[to];
        if (sz[to] > sz[ch[now]]) ch[now] = to;
    }
}

void dfs1(int now) {
    dfx[now] = ++ind;
    rdfx[ind] = now;
    if (ch[now]) {
        top[ch[now]] = top[now];
        dfs1(ch[now]);
    }
    for (auto to: e[now]) {
        if (to != ch[now]) {
            top[to] = to;
            dfs1(to);
        }
    }
}

class SegTree {
private:
    struct Node {
        int l, r;
        ll val, prd;
        bool flag;
    } t[N * 4];

    void up(int id) {
        t[id].val = t[id << 1].val * t[id << 1 | 1].val % MOD;
    }

    void down(int id) {
        if (!t[id].flag) return;
        t[id].flag = false;
        t[id << 1].val = t[id << 1].prd;
        t[id << 1].flag = true;
        t[id << 1 | 1].val = t[id << 1 | 1].prd;
        t[id << 1 | 1].flag = true;
    }

public:
    void build(int id, int l, int r) {
        t[id] = {l, r, 1, 1, false};
        if (l == r) {
            if (ch[rdfx[l]]) t[id].prd = sz[ch[rdfx[l]]];
            return;
        }
        build(id << 1, l, (l + r) / 2);
        build(id << 1 | 1, (l + r) / 2 + 1, r);
        up(id);
        t[id].prd = t[id << 1].prd * t[id << 1 | 1].prd % MOD;
    }

    void updateVal(int id, int pos, ll val) {
        if (t[id].l == t[id].r) {
            t[id].val = val;
            t[id].flag = false;
            return;
        }
        down(id);
        int mid = (t[id].l + t[id].r) / 2;
        if (pos <= mid) updateVal(id << 1, pos, val);
        else updateVal(id << 1 | 1, pos, val);
        up(id);
    }

    void updateFlag(int id, int l, int r) {
        if (l <= t[id].l && t[id].r <= r) {
            t[id].val = t[id].prd;
            t[id].flag = true;
            return;
        }
        down(id);
        int mid = (t[id].l + t[id].r) / 2;
        if (l <= mid) updateFlag(id << 1, l, r);
        if (r > mid) updateFlag(id << 1 | 1, l, r);
        up(id);
    }

    ll query() {
        return t[1].val;
    }
} st;

void solve() {
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        cin >> par[i];
        e[par[i]].push_back(i);
    }
    dfs0(1);
    top[1] = 1;
    dfs1(1);
    st.build(1, 1, n);

    ll ans = f[n];
    for (int i = 1; i <= n; i++) ans = ans * getInv(sz[i]) % MOD;
	printf( "%lld\n\n", ans );
    while (q--) {
        int x;
        cin >> x;

        vector<pii> v;
        int now = x;
        while (now) {
            v.emplace_back(dfx[top[now]], dfx[now]);
            now = par[top[now]];
        }

        st.updateVal(1, dfx[x], 1);
        for (int i = 0; i < v.size(); i++) {
            auto [l, r] = v[i];
            if (l < r) st.updateFlag(1, l, r - 1);
            if (i > 0) st.updateVal(1, r, sz[rdfx[v[i - 1].first]]);
        }

//        cout << st.query() << ' ';
        cout << ans * st.query() % MOD << '\n';
    }
}

int main() {
	freopen( "g.in", "r", stdin );
    init();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tc = 1;
//    cin >> tc;
    while (tc--) solve();
    return 0;
}
