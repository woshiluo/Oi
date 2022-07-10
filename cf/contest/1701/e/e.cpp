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

const int N = 5100;
const int INF = 0x3f3f3f3f;

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		static char s1[N], s2[N];
		static int f[N][N], g[N][N];

		memset( f, INF, sizeof(f) );
		memset( g, INF, sizeof(g) );

		cint n = read<int>();
		cint m = read<int>();
		scanf( "%s", s1 + 1 );
		scanf( "%s", s2 + 1 );

		for( int i = 0; i <= m; i ++ ) 
			f[0][i] = g[0][i] = i;
		for( int i = 1; i <= m; i ++ ) {
			for( int j = 1; j <= n; j ++ ) { 
				chk_Min( f[i][j], f[i][ j - 1 ] + 1 );
				if( s2[i] == s1[j] ) {
					chk_Min( f[i][j], f[ i - 1 ][ j - 1 ] );
				}
			}
		}
		for( int i = 1; i <= m; i ++ ) {
			for( int j = 1; j <= n; j ++ ) { 
				chk_Max( f[i][j], f[i][ j - 1 ] );
				g[i][j] = 0;
				if( s2[ n - i + 1 ] == s1[ m - j + 1 ] ) {
					chk_Max( g[i][j], g[ i - 1 ][ j - 1 ] + 1 );
				}
				chk_Max( f[i][j], f[i][j] + 1 );
			}
		}

		printf( "%d\n", f[m][n] );
	}
}
