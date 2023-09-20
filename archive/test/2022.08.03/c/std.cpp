#include <bits/stdc++.h>

using namespace std;

#define fr(i, x, y) for (int i = (x), _ed = (y); i <= _ed; i++) 
#define rp(i, x, y) for (int i = (x), _ed = (y); i >= _ed; i--) 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define LL long long


#define int long long

const int maxn = 1e6 + 45;
const int maxm = 1e6 + 45;

int n, q, mu[maxn];
struct edge {
	int x, y, w;
}edges[maxm];

int fa[maxn], siz[maxn];
int find(int x) {
	if (fa[x] == x) return x;
	else return find(fa[x]);
}
vector<int> tong[maxn];
int prime[maxn], tot, vis[maxn], is[maxn];
void sieve(int N) {
	mu[1] = 1;
	for (int i = 2; i <= N; i++) {
		if (!is[i]) {
			prime[++tot] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= tot && prime[j] * i <= N; j++) {
			is[prime[j] * i] = 1;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
	//for (int i = 1; i <= 10; i++) printf("%d %d\n", i, mu[i]);
}

LL res;
LL ans[maxn];
inline int ri() {
	int s = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') w = -1; c = getchar();}
	while (c >= '0' && c <= '9') { s = (s << 1) + (s << 3) + (c ^ 48); c = getchar();}
	return s * w;
}
pair<int, int*> sta[maxn];
void push(int &x, int y) {
	sta[++tot] = mp(x, &x);
	x = y;
}
void R(int x) {
	while (tot > x) {
		*(sta[tot].se) = sta[tot].fi;
		tot--;
	}
}
LL F(int x) {
	return x * (x - 1) / 2;
}
void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) return;
	if (siz[x] > siz[y]) swap(x, y);
	//printf("%d %d %d %d %d\n", siz[x], siz[y], F(siz[x]), F(siz[y]), F(siz[x] + siz[y]));
	push(res, res - F(siz[x]) - F(siz[y]) + F(siz[x] + siz[y]));
	push(fa[x], y);
	push(siz[y], siz[y] + siz[x]);
}
pair<int, int> tg[maxn];

vector<pair<int, int> > tax[maxn];
signed main() {
	sieve(1000000);
	n = ri();
	for (int i = 1; i < n; i++) {
		edges[i].x = ri(); edges[i].y = ri(); edges[i].w = ri();
		tong[edges[i].w].pb(i);
	}
	tot = 0;
	q = ri();
	fr (i, 1, q) {
		int x = ri(), y = ri();
		vis[x] = 1; tg[i] = mp(x, y);
	}
	fr (i, 1, n - 1) {
		int tmp = edges[i].w;
		if (!vis[i]) continue;
		for (int j = 0; j <= q; j++) {
			if (tg[j].fi == i) {
				tmp = tg[j].se;
			}
			for (int s = 1; s * s <= tmp; s++) {
				if (tmp % s) continue;
				if (mu[s]) tax[s].pb(mp(j, i));
				if (tmp / s != s && mu[tmp / s]) tax[tmp / s].pb(mp(j, i));
			}
		}
	}
	fr (i, 1, n) fa[i] = i, siz[i] = 1;
	int zzm = 0;
	fr (i, 1, 1000000) {
		if (mu[i] == 0) continue;
		//fr (i, 1, n) printf("sd %d %d\n", fa[i], siz[i]);
		for (int j = i; j <= 1000000; j += i) {
			for (int v : tong[j]) {
				//if (j == 10) printf("hh \n", tong[j].size());
				if (vis[v]) continue;
				merge(edges[v].x, edges[v].y);
				//printf("----%d %d----\n", edges[v].x, edges[v].y);
				//fr (i, 1, n) printf("sd %d %d\n", fa[i], siz[i]);
			}
		}
		sort(tax[i].begin(), tax[i].end());
		int asd = tot, now = 0;
		for (int j = 0; j <= q; j++) {
			while (now < tax[i].size() && tax[i][now].fi == j) {
				merge(edges[tax[i][now].se].x, edges[tax[i][now].se].y);
				now++;
			}
			//printf("%d %d\n", res, i);
			ans[j] += res * mu[i];
			R(asd);
		}
		R(0);
	}
	fr (i, 0, q) printf("%lld\n", ans[i]);
	return 0;
}
