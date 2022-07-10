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

const int N = 5100;

int a[N];
int g[N];
bool f[N][N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();

		for( int i = 1; i <= n; i ++ ) { 
			g[i] = 0;
			for( int j = 1; j <= n; j ++ ) {
				f[i][j] = false;
			}
		}

		for( int i = 1; i <= n; i ++ ) 
			a[i] = read<int>();

		for( int i = 1; i <= n; i ++ ) { 
			static int pool[N];
			for( int j = 1; j <= n; j ++ )
				pool[j] = 0;
			
			int max = 0;
			auto len = []( cint left, cint rig ) { return rig - left + 1; };
			for( int j = i; j <= n; j ++ ) {
				pool[ a[j] ] ++;
				chk_Max( max, pool[ a[j] ] );
				if( max <= ( len( i, j ) >> 1 ) && ( len( i, j ) % 2 == 0 ) ) 
					f[i][j] = true;
				else
					f[i][j] = false;
			}
		}

		int res = 0;
		f[1][0] = true;
		for( int i = 1; i <= n; i ++ ) {
			g[i] = f[1][ i - 1 ];
			for( int j = 1; j < i; j ++ ) {
				if( g[j] > 0 && a[i] == a[j] && ( ( j + 1 > i - 1 ) || f[ j + 1 ][ i - 1 ] ) ) 
					chk_Max( g[i], g[j] + 1 );
			}
			if( i == n || f[ i + 1 ][n] )
				chk_Max( res, g[i] );
		}
		printf( "%d\n", res );
	}
}
