/*
 * e.cpp 2024-09-25
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
constexpr T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
constexpr T Min( T a, T b ) { return a < b? a: b; }
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
constexpr T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 64;

int a[N][N];
int b[N][N];

bool valid( ci32 n ) {
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			bool f1 = ( i == 1 )? true: ( a[i][j] > a[ i - 1 ][j] );
			bool f2 = ( j == 1 )? true: ( a[i][j] > a[i][ j - 1 ] );
			if( (!f1) || (!f2) ) 
				return false;
		}
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			a[i][j] = read<i32>();
		}
	}

	if( valid(n) ) {
		printf( "0\n" );
		return 0;
	}


	for( int o = 1; o < 4; o ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= n; j ++ ) {
				b[i][j] = a[j][n - i + 1];
			}
		}
		memcpy( a, b, sizeof(b) );
		if( valid(n) ) {
			printf( "%d\n", o );
			return 0;
		}
	}

	return 0;
}
