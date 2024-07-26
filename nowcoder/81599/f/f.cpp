/*
 * f.cpp 2024-07-25
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

ci64 get_cen( ci64 x ) {
	ci64 half = ( x - 1LL ) / 2LL;
	ci64 base = ( 1LL + half ) * half;
	return base + ( ( x & 1LL )? 0: ( x >> 1LL ) );
}

ci64 get_leaf( ci64 x ) { return x * ( x - 1LL ) / 2LL; }

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		i64 x = read<i64>();

		if( x & 1 ) {
			i64 left = 0, rig = 2e9, res = 2e9;
			while( left <= rig ) {
				ci64 mid = ( left + rig ) >> 1LL;
				ci64 cur = ( mid << 1LL ) + 1;

				if( get_leaf(cur) - get_cen(cur) >= x ) {
					res = mid;
					rig = mid - 1;
				}
				else
					left = mid + 1;
			}


			printf( "%lld\n", ( res << 1LL ) + 1 );
		}
		else {
			i64 left = 0, rig = 4e9, res = 4e9;
			while( left <= rig ) {
				ci64 mid = ( left + rig ) >> 1LL;
				ci64 cur = mid;

				if( get_leaf(cur) - get_cen(cur) >= x ) {
					res = mid;
					rig = mid - 1;
				}
				else
					left = mid + 1;
			}


			printf( "%lld\n", res );
		}
	}
}
