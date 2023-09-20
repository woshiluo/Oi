#include <cmath>
#include <cstdio>
#include <cstring>

#include <queue>

inline int aabs( int a ) { return a < 0? -a: a; }

const int N = ( 3e4 + 1e3 ) * 120;
const int INF = 0x3f3f3f3f;

struct node {
	int cur, dis;
	bool operator< ( const node &b ) const { return ( this -> dis ) > b.dis; }
};

struct edge { int to, next, val; };

int n, m;
int b[N];

edge e[ N << 2 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to, int val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int* dij(int st) {
	const int n_size = n * 120;
	bool* vis = new bool[ n_size ];
	int* dis = new int[ n_size ];
	std::priority_queue<node> q;
	memset( vis, 0, sizeof(bool) * n_size );
	memset( dis, INF, sizeof(int) * n_size );
	dis[st] = 0;
	q.push( (node) { st, 0 } );
	while( !q.empty() ) {
		node top = q.top(); q.pop();
		int cur = top.cur;
		if( vis[cur] )
			continue;
		vis[cur] = true;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( dis[cur] + e[i].val < dis[ e[i].to ] ) {
				dis[ e[i].to ] = dis[cur] + e[i].val;
				if( vis[ e[i].to ] == false ) {
					q.push( (node) { e[i].to, dis[ e[i].to ] } );
				}
			}
		}
	}
	return dis;
}

int main() {
#ifdef woshiluo
	freopen( "loj.2877.in", "r", stdin );
	freopen( "loj.2877.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	int sqt = std::min( 100, (int)std::sqrt(n) );
	for( int i = 1; i <= sqt; i ++ ) {
		for( int j = 0; j < n; j ++ ) {
			int from = i * n + j, to = i * n + i + j;
			add_edge( from, j, 0 );

			if( to > i * n + n - 1 )
				continue;
			add_edge( from, to, 1 );
			add_edge( to, from, 1 );
		}
	}
	for( int i = 0; i < m; i ++ ) {
		int pos, p;
		scanf( "%d%d", &pos, &p );
		b[i] = pos;
		if( p <= sqt ) {
			add_edge( pos, p * n + pos, 0 ); 
		}
		else {
			int st = ( pos % p );
			for( int i = st; i < n; i += p ) {
				if( i == pos ) 
					continue;
				add_edge( pos, i, aabs( pos - i ) / p );
			}
		}
	}
	
	int* dis = dij( b[0] );
	
	printf( "%d\n", dis[ b[1] ] == INF? -1: dis[ b[1] ] );
}
