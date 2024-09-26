/*
 * c.cpp 2024-09-18
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
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i64> list( n * 2 + 1 );
		std::vector<i64> sum( n * 2 + 1 );
		for( int i = 1; i <= n; i ++ ) {
			list[i] = read<i64>();
			list[ i + n ] = list[i];
		}
		for( int i = 1; i <= ( n << 1 ); i ++ ) {
			sum[i] = sum[ i - 1 ] + list[i];
		}

		std::vector<i64> res( n + 1 );
		const auto query = [&] ( ci32 l, ci32 r ) { return sum[r] - sum[ l - 1 ]; };
		{
			for( int p1 = 1; p1 <= n; p1 ++ ) {
				i32 l = p1 + 1, r = p1 + n - 1;
				i32 res1 = l;
				while( l <= r ) {
					ci32 mid = ( l + r ) >> 1;
					if( query( p1 + 1, mid - 1 ) <= query( mid + 1, p1 + n - 1 ) ) {
						res1 = mid;
						l = mid + 1;
					}
					else {
						r = mid - 1;
					}
				}
				l = p1 + 1, r = p1 + n - 1;
				i32 res2 = r - 1;
				while( l <= r ) {
					ci32 mid = ( l + r ) >> 1;
					if( query( mid + 1, p1 + n - 1 ) <= query( p1 + 1, mid - 1 ) ) {
						res2 = mid;
						r = mid - 1;
					}
					else {
						l = mid + 1;
					}
				}
				res[p1] = sum[n] - Max( query( p1 + 1, res1 - 1 ) + list[res1], query( res2 + 1, p1 + n - 1 ) + list[res2] );
			}
		}
		printf( "%" PRId64 "\n", *std::max_element( res.begin() + 1, res.end() ) );
	}
}
