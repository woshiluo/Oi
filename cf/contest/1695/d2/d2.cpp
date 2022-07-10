/*
 * d2.cpp
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

const int N = 2e5 + 1e4;

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

int f[N], g[N];

int dfs( cint cur, cint la ) {
	int &res = f[cur];
	int &cnt = g[cur];
	res = 0, cnt = 0;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		cint tmp = dfs( e[i].to, cur );
		res += tmp;
		if( tmp == 0 )
			cnt ++;
	}
	res += Max( ( cnt - 1 ), 0 );
	return res;
}

void dfs2( cint cur, cint la, int &ans ) {
	chk_Min( ans, f[cur] + 1 );

	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;


		cint to = e[i].to;

		int res = f[cur], cnt = g[cur];
		res -= f[to];
		if( f[to] == 0 ) {
			if( cnt > 1 ) 
				res --;
			cnt --;
		}

		cint bf = f[to], bg = g[to];
		if( res == 0 ) {
			if( g[to] >= 1 )
				f[to] ++;
			g[to] ++;
		}
		else {
			f[to] += res;
		}

		dfs2( e[i].to, cur, ans );

		f[to] = bf; g[to] = bg;
	}

}

int main() {
#ifdef woshiluo
	freopen( "d2.in", "r", stdin );
	freopen( "d2.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();

		if( n == 1 ) {
			printf( "0\n" );
			continue;
		}

		ecnt = 0;
		for( int i = 1; i <= n; i ++ ) 
			ehead[i] = 0;

		for( int i = 1; i < n; i ++ ) {
			cint u = read<int>();
			cint v = read<int>();
			add_edge( u, v );
			add_edge( v, u );
		}

		int res = n;
		dfs( 1, 0 );
		dfs2( 1, 0, res );

		printf( "%d\n", res );
	}
}
