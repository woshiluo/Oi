/*
 * a.cpp
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
#include <cassert>

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

const int N = 5e5 + 1e4;
const int INF = 0x3f3f3f3f;

struct TreapNode {
	int id = 1;
};

int a[N], b[N];
int f[2][N], g[N];

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();

	for( int i = 1; i <= n; i ++ ) 
		a[i] = read<int>();
	for( int i = 1; i <= m; i ++ ) 
		b[i] = read<int>();

	std::sort( b + 1, b + m + 1 );

	int cur = 0, la = 1;

	memset( f, INF, sizeof(f) );
	memset( g, INF, sizeof(g) );
	g[0] = 0;

	for( int i = 1; i <= n; i ++, cur ^= 1, la ^= 1 ) {
		for( int j = 1; j <= m; j ++ ) {
			f[cur][j] = f[la][ j - 1 ] + 1;
		}

		for( int j = 1; j <= m; j ++ ) {
			if( b[j] >= a[ i - 1 ] ) 
				chk_Min( f[cur][j], g[ i - 1 ] + 1 );
			if( b[j] < a[i] ) 
				chk_Min( g[i], f[la][j] );
			if( b[j] == a[i] ) 
				chk_Min( f[cur][j], f[la][j] );
		}

		for( int j = 1; j <= m; j ++ ) 
			chk_Min( f[cur][j], f[cur][ j - 1 ] );

		if( a[i] >= a[ i - 1 ] ) 
			chk_Min( g[i], g[ i - 1 ] );
	}

	int res = INF;
	for( int i = 1; i <= m; i ++ ) 
		chk_Min( res, f[la][i] );
	chk_Min( res, g[n] );

	printf( "%d\n", res >= INF? -1: res );
}
