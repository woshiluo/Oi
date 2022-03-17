/*
 * d.cpp
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
 
const int N = 4e5 + 1e4;
 
struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( int from, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}
 
int f[N][2];
ll g[N][2];
void dfs( int cur, int la ) {
	f[cur][0] = f[cur][1] = 0;
	g[cur][0] = 1; g[cur][1] = ( la != 0 );
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la ) 
			continue;
		dfs( to, cur );
 
		f[cur][0] += Max( f[to][0], f[to][1] );
		f[cur][1] += f[to][0];
		if( f[to][0] == f[to][1] ) 
			g[cur][0] += Min( g[to][0], g[to][1] );
		else 
			g[cur][0] += g[to][ f[to][1] > f[to][0] ];
		g[cur][1] += g[to][0] + 1;
	}
	f[cur][1] ++;
}
 
int val[N];
bool good[N];
void tag( int cur, int la, bool k ) {
	good[cur] = k;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la ) 
			continue;
		if( k == false ) {
			bool flag = ( f[to][0] == f[to][1] ? g[to][1] < g[to][0]: f[to][1] > f[to][0] );
			tag( to, cur, flag );
		}
		else
			tag( to, cur, 0 );
	}
}

ll sum = 0;
void value( int cur, int la ) {
	val[cur] = 0;
	if( good[cur] ) 
		val[cur] += val[la];
	else 
		val[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la ) 
			continue;
		value( to, cur );
		if( good[cur] ) 
			val[cur] += val[to];
	}
	sum += val[cur];
}
 
int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int n = read<int>();
	if( n == 2 ) {
		printf( "%d %d\n%d %d", 2, 2, 1, 1 );
		return 0;
	}
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		u = read<int>(); v = read<int>();
		add_edge( u, v );
		add_edge( v, u );
	}

	dfs( 1, 0 );
 
	bool flag = ( f[1][1] == f[1][0]? g[1][1] < g[1][0]: f[1][1] > f[1][0] );

	tag( 1, 0, flag );
	value( 1, 0 );

	printf( "%d %lld\n", f[1][flag], g[1][flag] );
	for( int i = 1; i <= n; i ++ ) {
		printf( "%d ", val[i] );
	}
}
