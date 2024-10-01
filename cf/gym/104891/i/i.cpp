/*
 * i.cpp 2024-09-26
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
#include <cinttypes>

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

int main() {
#ifdef woshiluo
	freopen( "i.in", "r", stdin );
	freopen( "i.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 a = read<i32>();
		ci32 b = read<i32>();
		ci32 m = read<i32>();
		if( b < a ) {
			ci32 p1 = b;
			ci32 p2 = a;
			ci32 m1 = 1;
			ci32 m2 = 2;
			i64 max = 0;
			for( int k1 = 0; 1LL * k1 * p1 <= m; k1 ++ ) {
				ci32 less = m - k1 * p1;
				ci32 k2 = less / p2;
				ci32 rl = less - k2 * p2;
				ci32 rc = rl / a + 1;
				ci64 res = 1LL * ( m1 * k1 + m2 * k2 + 1 + rc ) * 160;
				chk_Max( max, res );
			}
			printf( "%" PRId64 "\n", max );
			continue;
		}
		else if( b % a == 0 ) {
			ci32 k = m / a + m / b + 2;
			printf( "%lld\n", k * 160LL );
			continue;
		}
		else {
			ci32 p1 = b;
			ci32 p2 = ( ( b / a ) + 1 ) * a;
			ci32 m1 = ( b / a ) + 1;
			ci32 m2 = ( b / a ) + 2;
			i64 max = 0;
			for( int k1 = 0; 1LL * k1 * p1 <= m; k1 ++ ) {
				ci32 less = m - k1 * p1;
				ci32 k2 = less / p2;
				ci32 rl = less - k2 * p2;
				ci32 rc = rl / a + 1;
				ci64 res = 1LL * ( m1 * k1 + m2 * k2 + 1 + rc ) * 160;
				chk_Max( max, res );
			}
			printf( "%" PRId64 "\n", max );
			continue;
		}
	}
	
	return 0;
}
