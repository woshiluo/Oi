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
} e[N];
int ehead[N], ecnt;
void add_edge( cint from, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from]; ehead[from] = ecnt;
}

ll l[N], r[N], val[N];
int dfs( cint cur ) {
	val[cur] = r[cur];
	if( ehead[cur] == 0 ) 
		return 1;

	val[cur] = 0;
	int res = 0, p = 0;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		res += dfs( e[i].to );
		val[cur] += val[ e[i].to ];
	}

	chk_Min( val[cur], r[cur] );
	if( val[cur] < l[cur] ) {
		val[cur] = r[cur];
		p = 1;
	}
	return res + p;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();

		ecnt = 0;
		for( int i = 1; i <= n; i ++ ) 
			ehead[i] = 0;

		for( int i = 2; i <= n; i ++ ) {
			add_edge( read<int>(), i );
		}
		for( int i = 1; i <= n; i ++ ) {
			l[i] = read<int>();
			r[i] = read<int>();
		}
		printf( "%d\n", dfs(1) );
	}
}
