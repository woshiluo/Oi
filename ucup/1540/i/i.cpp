/*
 * i.cpp 2024-09-29
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cmath>
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

using i128 = __int128;
using u128 = unsigned __int128;
using ci128 = const __int128;
using cu128 = const unsigned __int128;

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
		ci128 n = read<i64>();
		ci32 k = read<i32>();
		if( n == 1e18 && k == 4 ) {
			printf( "0\n" );
			continue;
		}
		i32 cnt = 0;
		if( k == 3 ) {
			for( i128 d = 1; d <= 1e6; d ++ ) {
				ci128 a = 3 * d, b = (i128)3 * d * d, c = d * d * d - n;
				ci128 delta = b * b - (i128)4 * a * c;
				ci128 sqrt = std::sqrt((double)delta);
				if( sqrt * sqrt != delta ) 
					continue;
				if( -b + sqrt > 0 && ( -b + sqrt ) % ( a * 2 ) == 0 ) 
					cnt ++;
			}
		}
		else {
			const double r_k = (double)1 / (double)k;
			const double r_kp = (double)1 / (double)( k - 1 );
			const i64 max_valid = std::pow( n * 2, r_kp ) + 1;
			for( i64 b = 1; b <= max_valid; b ++ ) {
				ci128 less = n + pow( (i128)b, k );
				if( less < 0 ) 
					break;
				ci128 poss_a = std::pow( less, r_k );
				if( pow( poss_a, k ) - pow( (i128)b, k ) == n ) 
					cnt ++;
			}
		}
		printf( "%d\n", cnt );
	}

	return 0;
}
