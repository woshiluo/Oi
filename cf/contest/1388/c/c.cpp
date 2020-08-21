// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/30 23:17:23 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 1e5 + 1e4;

int T;
int h[N], p[N], son[N];
int n, m;

struct edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

inline void init() {
	ecnt = 0;
//	memset( e, 0, sizeof(e) );
	memset( ehead, 0, sizeof(ehead) );
}

void readin() {
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &p[i] );
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &h[i] );
	}
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		add_edge( u ,v );
		add_edge( v, u );
	}
}

bool dfs( int cur, int la ) {
	int res = 0;
	son[cur] = p[cur];
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		if( dfs( e[i].to, cur ) == false ) 
			return false;
		res += h[ e[i].to ];
		son[cur] += son[ e[i].to ];
	}

	if( res == h[cur] ) 
		return ( p[cur] % 2 == 0 );
	if( res < h[cur] ) {
		if( h[cur] <= son[cur] ) {
			if( ( ( son[cur] - h[cur] ) % 2 ) == 0 ) 
				return true;
			return false;
		}
		return false;
	}
	if( res > h[cur] ) {
		int less = res - h[cur];
		if( p[cur] >= less ) {
			if( ( ( p[cur] - less ) % 2 ) == 0 ) 
				return true;
			return false;
		}
		return false;
	}
	return false;
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		init();
		readin();
		printf( "%s\n", dfs( 1, 0 )? "YES": "NO" );
	}
}
