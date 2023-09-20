/*
 * luogu.5829.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

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

const int N = 1e6 + 1e5;

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( cint cur, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int fa[N], size[N], mson[N], dep[N];/*{{{*/
void dfs1( cint cur, cint la ) {
	fa[cur] = la; dep[cur] = dep[la] + 1;
	size[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;

		dfs1( to, cur );
		size[cur] += size[to];

		if( size[to] > size[ mson[cur] ] )
			mson[cur] = to;
	}
}

int top[N];
void dfs2( cint cur ) {
	if( !top[cur] ) 
		top[cur] = cur;
	if( !mson[cur] ) 
		return ;

	top[ mson[cur] ] = top[cur];
	dfs2( mson[cur] );

	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		if( e[i].to == mson[cur] ) 
			continue;
		dfs2(to);
	}
}/*}}}*/

int get_lca( int from, int to ) {
	while( top[from] != top[to] ) {
		if( dep[ top[from] ] < dep[ top[to] ] ) 
			std::swap( from, to );
		from = fa[ top[from] ];
	}
	return dep[from] < dep[to]? from: to;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.5829.in", "r", stdin );
	freopen( "luogu.5829.out", "w", stdout );
#endif
	{
		static char str[N];
		static int nxt[N];
		scanf( "%s", str + 1 );
		cint n = strlen( str + 1 );
		int p = 0;
		nxt[1] = 0;
		add_edge( 1, 2 );
		for( int i = 2; i <= n; i ++ ) {  
			while( p && str[ p + 1 ] != str[i] ) 
				p = nxt[p];
			if( str[ p + 1 ] == str[i] ) 
				p ++;
			nxt[i] = p;
			add_edge( nxt[i] + 1, i + 1 );
		}

		dfs1( 1, 0 );
		dfs2(1);
	}

	int q = read<int>();
	while( q -- ) {
		cint u = read<int>(); cint v = read<int>();
		cint lca = get_lca( u + 1, v + 1 );
		if( lca == u + 1 || lca == v + 1 ) 
			printf( "%d\n", fa[lca] - 1 );
		else
			printf( "%d\n", lca - 1 );
	}
}
