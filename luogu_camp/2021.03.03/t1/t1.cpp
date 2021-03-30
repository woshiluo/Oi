#include <cstdio>
#include <cstring>

const int N = 1e5 + 1e4;

int T;
int a[N];
long long sg[N];

// Edge Start
struct edge {
	int to, next;
} e[ N ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}
// Edge End

void init() {
	ecnt = 0;
	memset( ehead, 0, sizeof(ehead) );
	memset( sg, 0, sizeof(sg) );
}

void readin() {
	int n;
	scanf( "%d", &n );
	for( int i = 2; i <= n; i ++ ) {
		int fa;
		scanf( "%d", &fa );
		add_edge( fa, i );
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
}

void dfs( int cur ) {
	sg[cur] = a[cur];
	for( int i = ehead[cur]; i; i = e[i].next ) {
		dfs( e[i].to );
		sg[cur] ^= ( sg[ e[i].to ] + 1 );
	}
}

int main() {
#ifdef woshiluo
	freopen( "t1.in", "r", stdin );
	freopen( "t1.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		init();
		readin();
		dfs(1);
		printf( "%s\n", sg[1]? "Alice": "Bob" );
//		printf( "%d\n", sg[1] );
	}
}
