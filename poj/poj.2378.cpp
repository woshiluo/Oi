#include <cstdio>

#include <algorithm>

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 11000;

// Edge Start 
struct edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

int n, a_cnt;
int son[N], a[N];

void dfs( int now, int la ) {
	son[now] = 1;
	int max_son = 0;
	for( int i = ehead[now]; i; i = e[i].next ) {
		if( la == e[i].to )
			continue;
		dfs( e[i].to, now );
		son[now] += son[ e[i].to ];
		max_son = Max( max_son, son[ e[i].to ] );
	}
	if( Max( max_son, n - son[now] ) <= n / 2 ) 
		a[ ++ a_cnt ] = now;
}

int main() {
#ifdef woshiluo
	freopen( "poj.2378.in", "r", stdin );
	freopen( "poj.2378.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1, u, v; i < n; i ++ ) {
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
	}
	dfs( 1, 0 );
	if( a_cnt == 0 ) {
		printf( "NONE\n" );
		return 0;
	}
	std::sort( a + 1, a + a_cnt + 1 );
	for( int i = 1; i <= a_cnt; i ++ ) 
		printf( "%d\n", a[i] );
}
