/*
 * b.cpp 2024-07-07
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
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	i32 k = read<i32>();
	int len = ( k / 25 ) + ( k % 25 != 0 ) + 1;
	if( len == 2 ) {
		printf( "%c%c", 'a', 'a' + k );
		return 0;
	}
	if( len == 3 ) {
		for( int p2 = 'a'; p2 <= 'z'; p2 ++ ) {
			{
				ci32 t = ( p2 - 'a' ) + ( p2 - 'b' );
				if( t == k ) {
					printf( "%c%c%c", 'a', p2, 'b' );
					return 0;
				}
			}
			{
				ci32 t = ( p2 - 'a' ) + ( p2 - 'a' );
				if( t == k ) {
					printf( "%c%c%c", 'a', p2, 'a' );
					return 0;
				}
			}
		}
		return -1;
	}
	for( int p2 = 'a'; p2 <= 'z'; p2 ++ ) {
		int tk = k - (p2 - 'a') * 2;
		int tlen = ( tk / 25 ) + ( tk % 25 != 0 ) + 1 + 2;
		if( tlen == len ) {
			printf( "%c%c%c", 'a', p2, 'a' );
			ci32 t = tk / 25;
			for( int i = 0; i < t; i ++ ) {
				if( i & 1 )
					printf( "a" );
				else
					printf( "z" );
			}
			if( tk % 25 != 0 ) {
				if( t & 1 )
					printf( "%c", 'z' - ( tk % 25 ) );
				else
					printf( "%c", 'a' + ( tk % 25 ) );
			}
			printf("\n" );
			return 0;
		}
	}
	return -1;
}
