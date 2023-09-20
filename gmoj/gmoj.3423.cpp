#include <cstdio>
#include <cstring>

inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 210;
const int INF = 0x3f3f3f3f;

int n, m, S, T;
bool f[N][N];


// Edge Start
struct edge {
	int to, next, val;
} e[ N * N * 3 ];
int ehead[N * 3], ecnt = 1;
inline void add_edge( int now, int to, int val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

int cur[N * 3], depth[N * 3], q[ N * N * N ];
int head, tail;

bool bfs() {
	memset( depth, 0, sizeof(depth) );
	head = tail = 0;
	q[head] = S;
	depth[S] = 1;
	while( head <= tail ) {
		for( int i = ehead[ q[head] ]; i; i = e[i].next ) {
			if( e[i].val > 0 && depth[ e[i].to ] == 0 ){
				depth[ e[i].to ] = depth[ q[head] ] + 1;
				q[ ++ tail ] = e[i].to;
			}
		}
		head ++;
	}
	return depth[T] != 0;
}

int dfs( int now, int dist ) {
	if( now == T )
		return dist;
		
	int flow = 0;
	for( int &i = cur[now]; i; i = e[i].next ) {
		if( depth[ e[i].to ] == depth[now] + 1 && e[i].val != 0 ) {
			int _dist = dfs( e[i].to, Min( dist, e[i].val ) );
			if( _dist > 0 ) {
				flow += _dist;
				dist -= _dist;
				e[i].val -= _dist;
				e[ i ^ 1 ].val += _dist;
				if( dist == 0 )
					return flow;
			}
		}
	}
	return flow;
}

int dinic() {
	int ans = 0;
	while( bfs() ) {
		memcpy( cur, ehead, sizeof(ehead) );
		while( int d = dfs( S, INF ) )
			ans += d;
	}
	return ans;
}

int main() {
#ifdef woshiluo
	freopen( "tmp.in", "r", stdin );
#endif
	scanf( "%d%d", &n, &m );
	while( m -- ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		f[u][v] = true;
	}
	
	S = 2 * n + 1, T = 2 * n + 2;
	
	// Floyd
	for( int k = 1; k <= n; k++ ) {
		for( int i = 1; i <= n; i++ ) {
			for( int j = 1; j <= n; j++ ) {
				f[i][j] = f[i][j] || ( f[i][k] && f[k][j] );
			}
		}
	}
	
	// Build Graph
	for( int i = 1; i <= n; i++ ) {
		add_edge( S, i, 1 );
		add_edge( i, S, 0 );
		add_edge( i + n, T, 1 );
		add_edge( T, i + n, 0 );
		
	}
	for( int i = 1; i <= n; i++ ) {
		for( int j = 1; j <= n; j++ ) {
			if( f[i][j] ) {
				add_edge( i, j + n, 1 );
				add_edge( j + n, i, 0 );
			}
		}
	}
	
	printf( "%d", n - dinic() );
}
