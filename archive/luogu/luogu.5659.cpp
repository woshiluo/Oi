/*
 * luogu.5659.cpp
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
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

const int N = 2100;

struct Graph {
	struct Edge {
		int to, next;
	} e[ N << 1 ];
	int ehead[N], block[N], ecnt;

	void init() {
		ecnt = 0;
		memset( ehead, 0, sizeof(ehead) );
		memset( block, 0, sizeof(block) );
	}

	void add_edge( cint from, cint to ) {
		ecnt ++;
		e[ecnt].to = to;
		e[ecnt].next = ehead[from];
		ehead[from] = ecnt;
	}
};

int dep[N], fa[N];
int get_min_id( cint cur, cint la, Graph &g, cint id[] ) {
	int res = cur; dep[cur] = dep[la] + 1; fa[cur] = la;
	for( int i = g.ehead[cur]; i; i = g.e[i].next ) {
		cint to = g.e[i].to;
		if( to == la || g.block[ ( i + 1 ) >> 1 ] ) 
			continue;
		cint nxt = get_min_id( to, cur, g, id );
		if( id[nxt] < id[res] ) 
			res = nxt;
	}
	return res;
}

void update_edge( int from, int to, Graph &g, int id[] ) {
	for( int i = g.ehead[from]; i; i = g.e[i].next ) { 
		g.block[ ( i + 1 ) >> 1 ] = true;
	}
	while( from != to ) {
		if( dep[from] < dep[to] ) 
			std::swap( from, to );

		int edge_id = 0;
		for( int i = g.ehead[ fa[from] ]; i; i = g.e[i].next ) {
			if( g.e[i].to == from ) {
				edge_id = i;
			}
		}

		g.block[ ( edge_id + 1 ) >> 1 ] = true;
		std::swap( id[from], id[ fa[from] ] );
		from = fa[from];
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.5659.in", "r", stdin );
	freopen( "luogu.5659.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		static Graph g;
		static int id[N];

		g.init();
		
		cint n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			id[i] = read<int>();
		}
		for( int i = 1; i < n; i ++ ) {
			cint u = read<int>();
			cint v = read<int>();
			g.add_edge( u, v );
			g.add_edge( v, u );
		}

		for( int i = 1; i <= n; i ++ ) {
			cint to = get_min_id( i, 0, g, id );
			update_edge( i, to, g, id );
		}

		for( int i = 1; i <= n; i ++ ) {
			printf( "%d ", id[i] );
		}
		printf( "\n" );

	}
}
