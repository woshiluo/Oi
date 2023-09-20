/*
 * e.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 2e5 + 1e4;
const int K = 20;

struct Set {/*{{{*/
	int fa[N];

	void init( cint n ) {
		for( int i = 0; i <= n; i ++ )
			fa[i] = i;
	}

	int& get_fa( cint cur ) {
		if( fa[cur] == cur ) 
			return fa[cur];
		int &cfa = get_fa( fa[cur] );
		fa[cur] = cfa;
		return cfa;
	}

	int& operator[] ( cint cur ) { return get_fa(cur); }
} set;/*}}}*/

struct Edge {/*{{{*/
	int to, next, val;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( cint cur, cint to, cint val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/

int st[N][K];

int dep[N];
int fa[N][K], max[N][K];
void dfs( cint cur, cint la ) {
	for( int k = 0; k < K; k ++ )
		fa[cur][k] = 0;
	fa[cur][0] = la;
	dep[cur] = dep[la] + 1;
	for( int k = 1; k < K; k ++ ) {
		if( fa[cur][ k - 1 ] && fa[ fa[cur][ k - 1 ] ][ k - 1 ] ) {
			fa[cur][k] = fa[ fa[cur][ k - 1 ] ][ k - 1 ];
			max[cur][k] = Max( max[cur][ k - 1 ], max[ fa[cur][ k - 1 ] ][ k - 1 ] );
		}
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		if( to == la ) 
			continue;
		max[to][0] = e[i].val;
		dfs( to, cur );
	}
}

int get_lca( int from, int to ) {
	if( dep[from] < dep[to] ) 
		std::swap( from, to );

	for( int k = K - 1; k >= 0; k -- ) 
		if( fa[from][k] && dep[ fa[from][k] ] >= dep[to] ) 
			from = fa[from][k];

	if( from == to ) 
		return from;

	for( int k = K - 1; k >= 0; k -- ) 
		if( fa[from][k] && fa[to][k] && fa[from][k] != fa[to][k] ) {
			from = fa[from][k];
			to = fa[to][k];
		}

	return fa[from][0];
}

int query( int from, int to ) {
	if( from == to ) 
		return 0;
	cint lca = get_lca( from, to );

	int res = 0;
	for( int k = K - 1; k >= 0; k -- ) {
		if( fa[from][k] && dep[ fa[from][k] ] > dep[lca] ) {
			chk_Max( res, max[from][k] );
			from = fa[from][k];
		}
	}
	for( int k = K - 1; k >= 0; k -- ) {
		if( fa[to][k] && dep[ fa[to][k] ] > dep[lca] ) {
			chk_Max( res, max[to][k] ); 
			to = fa[to][k];
		}
	}

	if( from != lca ) 
		chk_Max( res, max[from][0] );
	if( to != lca ) 
		chk_Max( res, max[to][0] );

	return res;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();
		cint q = read<int>();

		set.init(n); ecnt = 0;
		for( int i = 1; i <= n; i ++ )
			ehead[i] = 0;

		for( int i = 1; i <= m; i ++ ) {
			cint u = read<int>();
			cint v = read<int>();

			if( set[u] == set[v] ) 
				continue;
			set[u] = set[v];

			add_edge( u, v, i );
			add_edge( v, u, i );
		}

		dfs( 1, 0 );

		for( int i = 1; i <= n; i ++ ) 
			for( int k = 0; k < K; k ++ ) 
				st[i][k] = 0;

		for( int i = 1; i < n; i ++ ) {
			st[i][0] = query( i, i + 1 );
		}

		for( int k = 1; k < K; k ++ ) {
			for( int i = 1; i < n; i ++ ) {
				if( i + ( 1 << k ) - 1 < n )
					st[i][k] = Max( st[i][ k - 1 ], st[ i + ( 1 << ( k - 1 ) ) ][ k - 1 ] );
			}
		}

		for( int _ = 1; _ <= q; _ ++ ) {
			cint l = read<int>();
			cint r = read<int>() - 1;

			if( r < l ) {
				printf( "0 " );
				continue;
			}

			cint k = std::log(( r - l + 1 )) / std::log(2);

			cint res = Max( st[l][k], st[ r - ( 1 << k ) + 1 ][k] );

			printf( "%d ", res );
		}
		printf( "\n" );
	}
}
