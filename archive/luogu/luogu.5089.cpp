#include <cstdio>

const int N = 4e5 + 1e4;

int n, m, k;
bool vis[N];

// Edge Start 
struct edge { int to, next; };

int ehead[N], ecnt;
edge e[ N << 1 ];
inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

void dfs( int cur ) {
	vis[cur] = true;
	for( int i = ehead[cur]; i; i = e[i].next ){
		if( vis[ e[i].to ] == false ) 
			dfs( e[i].to );
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.5089.in", "r", stdin );
	freopen( "luogu.5089.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &k );
	while( k -- ) {
		int x, y;
		scanf( "%d%d", &x, &y );
		add_edge( x, y + n );
		add_edge( y + n, x );
	}
	
	int cnt = 0;
	for( int i = 1; i <= m + n; i ++ ) {
		if( vis[i] == false ) {	
			cnt ++;
			dfs(i);
		}
	}
	printf( "%d\n", cnt - 1 );

	return 0;
}
