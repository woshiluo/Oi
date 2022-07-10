/*
 * c.cpp
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

const int N = 1100;
const int INF = 0x3f3f3f3f;

int a[N][N];
int f[N][N], g[N][N];

int main() {
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) { 
				a[i][j] = read<int>();
				f[i][j] = -INF; g[i][j] = INF;
			}
		}
		if( ( n + m - 1 ) & 1 ) {
			printf( "NO\n" );
			continue;
		}
		f[1][1] = g[1][1] = a[1][1];
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				if( i > 1 ) {
					chk_Max( f[i][j], f[ i - 1 ][j] + a[i][j] );
					chk_Min( g[i][j], g[ i - 1 ][j] + a[i][j] );
				}
				if( j > 1 ) {
					chk_Max( f[i][j], f[i][ j - 1 ] + a[i][j] );
					chk_Min( g[i][j], g[i][ j - 1 ] + a[i][j] );
				}
			}
		}
		if( f[n][m] < 0 || g[n][m] > 0 ) 
			printf( "NO\n" );
		else
			printf( "YES\n" );
	}
}
