/*
 * d1.cpp
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

int dfs( cint cur, cint la ) {
	int res = 0, cnt = 0;
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

int main() {
#ifdef woshiluo
	freopen( "d1.in", "r", stdin );
	freopen( "d1.out", "w", stdout );
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
		for( int i = 1; i <= n; i ++ ) {
			chk_Min( res, dfs( i, 0 ) + 1 );
		}

		printf( "%d\n", res );
	}
}
