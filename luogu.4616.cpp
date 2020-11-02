#include <cstdio>
#include <cstring>

#include <algorithm>

const int INF = 0x3f3f3f3f;
const int N = 2e5 + 1e4;
const int K = 25;

int n, m, q;
int fa[N][K], min[N][K], dep[N];

// Set Start
struct Set {
	int fa[N];
	Set(int n) {
		for( int i = 0; i <= n; i ++ ) {
			fa[i] = i;
		}
	}
	int& get_fa( int cur ) {
		if( fa[cur] == cur ) 
			return fa[cur];
		int &p = get_fa( fa[cur] );
		fa[cur] = p;
		return p;
	}
	inline int& operator[] ( int index ) {
		return this -> get_fa(index);
	}
};
// Set End

// Edge Start
struct edge {
	int to, val, next;
} e[ N << 1 ];
int ecnt, ehead[N];
inline void add_edge( int cur, int to, int val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}
// Edge End

void dfs( int cur, int la ) {
	for( int k = 1; k < K; k ++ ) {
		if( fa[ fa[cur][ k - 1 ] ][ k - 1 ] == 0 )
			continue;
		fa[cur][k] = fa[ fa[cur][ k - 1 ] ][ k - 1 ];
		min[cur][k] = std::min( min[cur][k], std::min( min[cur][ k - 1 ], min[ fa[cur][ k - 1 ] ][ k - 1 ] ) );
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == fa[cur][0] ) 
			continue;
		fa[to][0] = cur;
		min[to][0] = e[i].val;
		dep[to] = dep[cur] + 1;
		dfs( to, cur );
	}
}

int query( int from, int to ) {
	int res = INF;
	if( dep[from] < dep[to] ) 
		std::swap( from, to );
	for( int k = K - 1; k >= 0; k -- ) {
		if( dep[ fa[from][k] ] >= dep[to] ) {
			res = std::min( res, min[from][k] );
			from = fa[from][k];
		}
	}
	if( from == to ) 
		return res;
	for( int k = K - 1; k >= 0; k -- ) {
		if( fa[from][k] != fa[to][k] ) {
			res = std::min( res, std::min( min[from][k], min[to][k] ) );
			from = fa[from][k];
			to = fa[to][k];
		}
	}
	return std::min( res, std::min( min[from][0], min[to][0] ) );
}

int main() {
#ifdef woshiluo
	freopen( "luogu.4616.in", "r", stdin );
	freopen( "luogu.4616.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &q );
	// Init
	Set set(n);
	for( int i = m; i >= 1; i -- ) {
		for( int j = i + i; j <= n; j += i ) {
			//int u = get_fa(i), v = get_fa(j);
			int u = set[i], v = set[j];
			if( u != v ) {
				set[u] = set[v];
				add_edge( i, j, i );
				add_edge( j, i, i );
			}
		}
	}
	// Processing
	memset( min, INF, sizeof(min) );
	// min[1][0] = 0;
	dep[1] = 1;
	dfs( 1, 0 );
	// Answer
	while( q -- ) {
		int u ,v;
		scanf( "%d%d", &u, &v );
		printf( "%d\n", m - query( u, v ) + 1 );
	}
}
