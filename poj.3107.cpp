#include <cstdio>

#include <algorithm>

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 5e4 + 1e3;

int n;
int son[N];

struct node {
	int id, val;
} a[N];

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

void dfs( int now, int la ) {
	int max_son = 0;
	son[now] = 1;
	for( int i = ehead[now]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, now );
		son[now] += son[ e[i].to ];
		max_son = Max( max_son, son[ e[i].to ] );
	}

	a[now] = (node) { now, Max( n - son[now], max_son ) };
}

bool cmp( node a, node b ) { 
	if( a.val == b.val ) 
		return a.id < b.id;
	return a.val < b.val;
}

int main() {
#ifdef woshiluo
	freopen( "poj.3107.in", "r", stdin );
	freopen( "poj.3107.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1, u, v; i < n; i ++ ) {
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
	}

	dfs( 1, 0 );

	std::sort( a + 1, a + n + 1, cmp );

	for( int i = 1; i <= n; i ++ ) {
		if( i != 1 && a[i].val != a[ i - 1 ].val ) 
			break;
		printf( "%d ", a[i].id );
	}
}
