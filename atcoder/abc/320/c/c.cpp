/*
 * c.cpp 2023-09-17
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

#include <vector>
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

int a[3][N];
bool f[N][ 1 << 3 ];

inline int full_pow( cint cur ) { return 1 << cur; }
bool chk_pos( cint cur, cint pos ) { return ( cur >> pos ) & 1; }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	cint n = read<int>();
	for( int i = 0; i < 3; i ++ )
		for( int j = 0; j < n; j ++ )
			scanf( "%1d", &a[i][j] );

	int ans = 5 * n;
	for( int p = 0; p < 10; p ++ ) {
		memset( f, 0, sizeof(f) );
		f[0][0] = 1;
		for( int i = 0; i <= n * 4; i ++ ) {
			for( int j = 0; j < full_pow(3); j ++ ) {
				if( f[i][j] == false )
					continue;
				f[ i + 1 ][j] = f[i][j];
				if( j == full_pow(3) - 1 ) {
					chk_Min( ans, i );
				}
				for( int k = 0; k < 3; k ++ ) {
					if( !chk_pos( j, k ) && a[k][ i % n ] == p ) {
						f[ i + 1 ][ j | full_pow(k) ] = 1;
					}
				}
			}
		}
	}

	if( ans == 5 * n )
		printf( "-1\n" );
	else
		printf( "%d\n", ans - 1 );


}
