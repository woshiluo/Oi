// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/14 22:52:18 
#include <cstdio>
#include <cstring>

#include <algorithm>

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }

const int N = 1e5 + 1e4;

// Edge Start
struct edge {
	int to, next, val;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int now, int to, int val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	e[ecnt].val = val;
	ehead[now] = ecnt;
}
// Edge End

struct node { long long val; int id; } max[N];
bool cmp( node _a, node _b ) { return _a.val < _b.val; }

int n, x, y;
int son[N], val[N];

void dfs( int now, int la ) {
	son[now] = 1;
	for( int i = ehead[now]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, now );
		son[now] += son[ e[i].to ];
		max[ e[i].val ].val = ( 1LL * son[ e[i].to ] * ( n - son[ e[i].to ] ) );
	}
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1, u, v; i < n; i ++ ) {
		max[i].id = i;
		scanf( "%d%d", &u, &v );
		add_edge( u, v, i );
		add_edge( v, u, i );
	}

	dfs( 1, 0 );

	std::sort( max + 1, max + n, cmp );

	for( int i = 1; i < n; i ++ ) {
		val[ max[i].id ] = i - 1;
	}

	for( int i = 1; i < n; i ++ ) {
		printf( "%d\n", val[i] );
	}
}
