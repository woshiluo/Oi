/*
 * b.cpp 2024-05-31
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

int full_pow( ci32 k ) { return 1 << k; }
int full_bit( ci32 k ) { return ( 1 << ( k + 1 ) ) - 1; }
int chk_pos( ci32 n, ci32 k ) { return ( n >> k ) & 1; }

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		i32 base = 0;
		for( int k = 0; k <= 30; k ++ ) {
			if( chk_pos( n, k ) ) {
				base |= 1 << k;
			}
			else {
				ci32 target = ( n & ( ~( full_bit(k) ) ) | full_pow(k) );
				if( target - n <= m ) {
					base |= 1 << k;
				}
				if( full_pow(k) <= n ) {
					ci32 atar = ( n & full_bit(k) ) + 1;
					if( atar <= m ) {
						base |= 1 << k;
					}
				}
			}
		}
		printf( "%d\n", base );
	}
	return 0;
}
