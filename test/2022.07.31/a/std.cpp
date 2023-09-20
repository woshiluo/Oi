//Code By CXY07 - It's My Fiesta.
#include<bits/stdc++.h>
using namespace std;

//#define FILE
//#define int long long
#define randint(l, r) (rand() % ((r) - (l) + 1) + (l))
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define popc(x) __builtin_popcount(x)
#define inv(x) qpow((x), mod - 2)
#define lowbit(x) ((x) & (-(x)))
#define ull unsigned long long
#define pii pair<int, int>
#define LL long long
#define mp make_pair
#define pb push_back
#define scd second
#define vec vector
#define fst first
#define endl '\n'
#define y1 _y1

const int MAXN = 2e6 + 10;
const int INF = 2e9;
const double eps = 1e-6;
const double PI = acos(-1);
//const int mod = 1e9 + 7;
//const int mod = 998244353;
//const int G = 3;
//const int base = 131;

int n, m, rt = 0, Ans, cnt;
int a[MAXN], b[MAXN], f0;
int ls[MAXN], rs[MAXN], rnk[MAXN], siz[MAXN];
int mn[MAXN], tag[MAXN], val[MAXN], cov[MAXN];

template<typename T> inline bool read(T &a) {
	a = 0; char c = getchar(); int f = 1;
	while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
	while(c >= '0' && c <= '9') { a = a * 10 + (c ^ 48); c = getchar(); }
	return a *= f, true;
}

template<typename A, typename ...B>
inline bool read(A &x, B &...y) { return read(x) && read(y...); }

int New(int v) {
	++cnt; mn[cnt] = val[cnt] = v, tag[cnt] = 0, cov[cnt] = -1;
	ls[cnt] = rs[cnt] = 0, siz[cnt] = 1, rnk[cnt] = rand();
	return cnt;
}

void pushup(int x) { 
	siz[x] = siz[ls[x]] + siz[rs[x]] + 1; 
	mn[x] = min({ mn[ls[x]], mn[rs[x]], val[x] });
}

void push1(int x, int v) { 
	if(x && mn[x] < INF) { 
		mn[x] += v, tag[x] += v; 
		if(val[x] < INF) val[x] += v;
	} 
}
void push2(int x, int v) { if(x) { mn[x] = val[x] = v, tag[x] = 0, cov[x] = v; } }

void pushdown(int x) { 
	if(~cov[x]) push2(ls[x], cov[x]), push2(rs[x], cov[x]), cov[x] = -1;
	if(tag[x]) push1(ls[x], tag[x]), push1(rs[x], tag[x]), tag[x] = 0; 
}

void split(int x, int &a, int &b, int v) {
	if(!x) return a = b = 0, void();
	pushdown(x);
	if(siz[ls[x]] + 1 <= v) { a = x; split(rs[x], rs[a], b, v - siz[ls[x]] - 1); } 
	else { b = x; split(ls[x], a, ls[b], v); }
	pushup(x);
}

int merge(int &x, int a, int b) {
	if(!a || !b) return x = (a | b);
	pushdown(a), pushdown(b);
	if(rnk[a] < rnk[b]) { x = a; merge(rs[x], rs[a], b); } 
	else { x = b; merge(ls[x], a, ls[b]); }
	pushup(x); return x;
}

int GetV(int rt, int p) {
	int cur = rt;
	while(p) {
		pushdown(cur);
		if(siz[ls[cur]] >= p) { cur = ls[cur]; continue; }
		p -= siz[ls[cur]];
		if(p > 1) { --p; cur = rs[cur]; continue; }
		else break;
	}
	return val[cur];
}

void print(int rt) {
	pushdown(rt);
	if(ls[rt]) print(ls[rt]);
	printf("%d ", val[rt]);
	if(rs[rt]) print(rs[rt]);
}

void chkmin(int &x, int v) {
	if(v >= INF) return;
	int num = 0, c = x, p = 0, q = 0;
	while(c) {
		pushdown(c);
		if(val[c] >= v) { num += siz[ls[c]] + 1; c = rs[c]; } 
		else c = ls[c];
	}
	split(x, p, q, num); assert(mn[p] >= v);
	push2(p, v); merge(x, p, q);
}

signed main () {
	freopen("a.in", "r", stdin);
	freopen("a.ans", "w", stdout);
	read(n), read(m); mn[0] = INF;
	for(int i = 1; i <= n; ++i) read(a[i]);
	for(int i = 1; i <= m; ++i) read(b[i]);
	sort(b + 1, b + m + 1); f0 = 0;
	for(int i = 1; i <= m; ++i) merge(rt, rt, New(INF));
	for(int i = 1, L, R, p, q, o, t, g0, w; i <= n; ++i) {
		p = q = t = o = 0, g0 = INF;
		w = lower_bound(b + 1, b + m + 1, a[i]) - b - 1;
		if(w) g0 = GetV(rt, w);
		if(a[i - 1] <= a[i]) g0 = min(g0, f0);
		L = lower_bound(b + 1, b + m + 1, a[i]) - b;
		R = upper_bound(b + 1, b + m + 1, a[i]) - b - 1;
		if(b[L] == a[i]) {
			split(rt, p, q, L - 1);
			if(siz[p]) split(p, p, o, siz[p] - 1);
			push1(p, 1);
			if(L > 1) merge(p, New(INF), p);
			split(q, q, t, R - L + 1); assert(siz[q] == R - L + 1);
			if(siz[t]) split(t, t, o, siz[t] - 1);
			push1(t, 1);
			if(R < m) merge(t, New(INF), t);
			chkmin(t, GetV(q, R - L + 1));
			merge(rt, p, merge(q, q, t));
		} else {
			t = 0; split(rt, p, t, m - 1); assert(siz[p] == m - 1);
			val[t] = mn[t] = INF; push1(p, 1);
			merge(rt, t, p);
		}
		w = lower_bound(b + 1, b + m + 1, a[i - 1]) - b;
		p = q = 0; split(rt, p, q, w - 1); 
		chkmin(q, f0 + 1); merge(rt, p, q); f0 = g0;
		assert(siz[rt] == m);
	}
	Ans = min(f0, mn[rt]);
	if(Ans > (int)5e5) puts("-1");
	else printf("%d\n", Ans);
	return 0;
}
