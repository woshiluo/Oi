#include <cstdio>
#include <cstring>

inline int Min(int a, int b) { return a < b? a : b; }
inline long long Max(long long a, long long b) { return a > b? a : b; }

const int N = 2100;

int n, m;
int size[N];

// Edge Start 
struct edge {
	int to, val, next;
} e[N << 1];
int ehead[N], ecnt;

inline void add_edge(int now, int to, int val) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

// DP Start 
long long f[N][N];
void dp(int now, int la) {
	size[now] = 1;
	f[now][0] = f[now][1] = 0;
	for(int i = ehead[now]; i; i = e[i].next) {
		if( e[i].to == la ) 
			continue;
		dp(e[i].to, now);
		size[now] += size[ e[i].to ];
		for(int j = Min(size[now], m); j >= 0; j--) {
			for(int k = 0; k <= Min(size[ e[i].to ], j); k++) {
				if( f[now][ j - k ] == -1 )
					continue;
				long long val = 1LL * ( 1LL * k * ( m - k ) + 1LL * ( size[ e[i].to ] - k ) * ( n - m - size[ e[i].to ] + k ) ) * e[i].val;
				f[now][j] = Max( f[now][j], f[now][j - k] + f[ e[i].to ][k] + val);
			} 
		}
	}
}
// DP End

int main() {
#ifdef woshiluo
	freopen("luogu.3177.in", "r", stdin);
	freopen("luogu.3177.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v, w; i < n; i++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}

	memset(f, -1, sizeof(f));
	dp(1, 0);
	
	printf("%lld", f[1][m]);
	fclose(stdin);
	fclose(stdout);
}
