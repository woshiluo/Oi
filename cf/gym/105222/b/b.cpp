/*
 * b.cpp 2024-09-11
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
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		std::vector<i32> a(6);
		for( int i = 1; i <= 5; i ++ ) 
			a[i] = read<i32>();
		i64 res = 0;
		{
			ci32 k = ( a[3] >> 1 );
			a[3] -= ( k << 1 );
			res += k;
		}
		{
			ci32 k = Min( a[2], a[4] );
			a[2] -= k;
			a[4] -= k;
			res += k;
		}
		{
			for( int i = 1; i <= 4; i ++ ) {
				ci32 k = Min( a[i], a[5] );
				a[i] -= k;
				a[5] -= k;
				res += k;
			}
			ci32 k = ( a[5] >> 1 );
			a[5] -= ( k << 1 );
			res += k;
		}

		// 3 2 x
		if( a[2] && a[3] ) {
			{
				ci32 k = std::min( { a[1], a[2], a[3] } );
				res += k;
				a[1] -= k; a[2] -= k; a[3] -= k;
			}
			{
				ci32 k = std::min( { ( a[2] >> 1 ), a[3] } );
				res += k;
				a[2] -= k; a[2] -= k; a[3] -= k;
			}
			{
				ci32 k = std::min( { a[2], ( a[3] >> 1 ) } );
				res += k;
				a[2] -= k; a[3] -= k; a[3] -= k;
			}
		}

		// 4 x x
		if( a[4] ) {
			{
				ci32 tot = Min( ( a[1] + a[2] + a[3] ) >> 1, a[4] );
				res += tot;
				a[4] -= tot;
				{
					i32 cnt = tot * 2;
					for( int i = 1; i <= 3; i ++ ) {
						ci32 k = Min( a[i], cnt );
						cnt -= k;
						a[i] -= k;
					}
				}
			}
			if( a[4] >= 2 ) {
				// 4 4 x
				{
					ci32 tot = a[1] + a[2] + a[3];
					if( tot ) {
						res += 1;
						a[1] = a[2] = a[3] = 0;
						a[4] -= 2;
					}
				}
				// 4 4 4
				{
					ci32 k = ( a[4] / 3 );
					res += k;
					a[4] %= 3;
				}
			}
		}

		res += ( 1LL * a[1] + 2LL * a[2] + 3LL * a[3] ) / 6;

		printf( "%" PRId64 "\n", res );
	}
}
