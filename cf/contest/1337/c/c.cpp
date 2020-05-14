// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/15 22:53:27 
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
T chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
T chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 2e5 + 1e4;

struct edge { int to, next; };

int n, k;
int son[N], dep[N], val[N], id[N];

// Edge Start
edge e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

bool cmp( int a, int b ) { return val[a] > val[b]; }

void dfs( int now, int la ) {
	son[now] = 1; dep[now] = dep[la] + 1;
	for( int i = ehead[now]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la )
			continue;
		dfs( to, now );
		son[now] += son[to];
	}
	val[now] = dep[now] - son[now];
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &k );
	for( int i = 1, u, v; i < n; i ++ ) {
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
	}
	dfs( 1, 0 );

	for( int i = 1; i <= n; i ++ ) {
		id[i] = i;
	}
	std::sort( id + 1, id + n + 1, cmp );

	long long ans = 0;
	for( int i = 1; i <= k; i ++ ) {
		ans += val[ id[i] ];
	}
	printf( "%lld", ans );
}
