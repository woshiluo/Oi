/*
 * d.cpp 2024-07-20
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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> a( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<i32>();
			a[i] += ( a[i] & 1 );
		}
		std::vector<i32> f[4];
		// 0 00
		// 1 01
		// 2 10
		// 3 11
		f[0].resize( n + 1, n + 1 ), f[1].resize( n + 1, n + 1 );
		f[2].resize( n + 1, n + 1 ), f[3].resize( n + 1, n + 1 );
		f[0][0] = 0;
		for( int i = 1; i <= n; i ++ ) {
			f[0][i] = std::min( { f[0][ i - 1 ], f[1][ i - 1 ], f[2][ i - 1 ], f[3][ i - 1 ] } ) + 1;
			if( a[i] == 2 ) {
				chk_Min( f[0][i], f[2][ i - 1 ] );
				chk_Min( f[0][i], f[3][ i - 1 ] );
				f[2][i] = std::min( { f[0][ i - 1 ], f[1][ i - 1 ], f[2][ i - 1 ], f[3][ i - 1 ] } ) + 1;
			}
			else if( a[i] == 4 ) {
				chk_Min( f[1][i], f[2][ i - 1 ] + 1 );
				chk_Min( f[2][i], f[1][ i - 1 ] + 1 );

				chk_Min( f[0][i], f[3][ i - 1 ] );

				f[3][i] = std::min( { f[0][ i - 1 ], f[1][ i - 1 ], f[2][ i - 1 ], f[3][ i - 1 ] } ) + 2;
			}
			else if( a[i] == 0 )
				f[0][i] = std::min( { f[0][ i - 1 ], f[1][ i - 1 ], f[2][ i - 1 ], f[3][ i - 1 ] } );
		}
		printf( "%d\n", std::min( { f[0][n], f[1][n], f[2][n], f[3][n] } ) );
	}
}
