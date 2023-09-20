/*
 * b.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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

const int N = 2e5 + 1e4;

ll ans = 0;
int f[N], g[N];

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt; inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

void dfs( int cur, int la ) {
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la )
			continue;
		int to = e[i].to;
		dfs( to, cur );
		int tmp = Min( Min( g[cur], g[to] ), Min( f[cur], f[to] ) );
		g[cur] -= tmp; ans -= tmp;
	}
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		f[i] = read<int>();
		g[i] = f[i] * 2;
		ans += f[i];
	}
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		u = read<int>(); v = read<int>();
		add_edge( u, v );
		add_edge( v, u );
	}

	dfs( 1, 0 );
	printf( "%lld\n", ans );
}
