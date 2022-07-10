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

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <set>
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

const int N = 1 << 20;

struct Edge { int to, next, id; } e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( cint from, cint to, cint id ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	e[ecnt].id = id;
	ehead[from] = ecnt;
}

std::set<int> set[2];

int node_val[N], edge_val[N];

void dfs( int cur, int la, int val, int base ) {
	val ^= node_val[cur];

	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la )
			continue;

		int id = e[i].id;

		int p = ( val >= base );
		cint to = e[i].to;
		edge_val[id] = *set[p].begin();
		set[p].erase( edge_val[id] );
		node_val[to] = edge_val[id] + ( p? -1: 1 ) * base;
		set[ p ^ 1 ].erase( node_val[to] );

		dfs( e[i].to, cur, val ^ edge_val[id], base );
	}
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint k = read<int>();
		cint n = ( 1 << k );

		ecnt = 0;
		for( int i = 1; i <= n; i ++ ) 
			ehead[i] = 0;

		for( int i = 1; i < n; i ++ ) {
			int u, v;
			u = read<int>();
			v = read<int>();
			add_edge( u, v, i );
			add_edge( v, u, i );
		}
		for( int i = 1; i < n; i ++ ) {
			set[0].insert(i);
			set[1].insert( i + n );
		}
		
		node_val[1] = n;
		dfs( 1, 0, 0, n );

		printf( "%d\n", 1 );
		for( int i = 1; i <= n; i ++ ) 
			printf( "%d ", node_val[i] );
		printf( "\n" );
		for( int i = 1; i < n; i ++ ) 
			printf( "%d ", edge_val[i] );
		printf( "\n" );
	}
}
