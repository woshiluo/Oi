#include <cstdio>

#include <queue>

inline long long Max( long long a, long long b ) { return a > b? a: b; }

const int N = 1e5 + 1e4;
const long long INF = ( 1LL << 60 );

struct edge { int to, next; };

int n;
long long a[N];

// Edge Start{{{
int ehead[N], ecnt;
edge e[ N << 1 ];
inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End}}}

long long f[N][3];
void dfs( int cur, int la ) {
	long long son_sum = 0, max_f1 = -INF, max_f2 = -INF;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, cur );
		long long cur_0 = f[ e[i].to ][0];
		son_sum += cur_0;
		max_f1 = Max( f[ e[i].to ][1] - cur_0, max_f1 );
		max_f2 = Max( f[ e[i].to ][2] - cur_0, max_f2 );
	}
	f[cur][1] = son_sum + Max( a[cur], max_f1 );
	f[cur][2] = son_sum + Max( -a[cur], max_f2 );
	f[cur][0] = Max( f[cur][1] - a[cur], f[cur][2] + a[cur] );
} 

int main() {
#ifdef woshiluo
	freopen( "luogu.6293.in", "r", stdin );
	freopen( "luogu.6293.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lld", &a[i] );
	}
	for( int i = 1, u, v; i < n; i ++ ) {
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
	}

	dfs( 1, 0 );
	printf( "%lld\n", f[1][0] );
}
