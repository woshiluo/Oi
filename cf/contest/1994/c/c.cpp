/*
 * c.cpp 2024-07-20
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
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 x = read<i32>();

		std::vector<i64> a( n + 1 ), sum( n + 1 ), r( n + 1, -1 ), suf( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<i32>();
			sum[i] = sum[ i - 1 ] + a[i];
		}

		auto query_sum = [&]( ci32 left, ci32 rig ) { return sum[rig] - sum[ left - 1 ]; };

		for( int i = 1; i <= n; i ++ ) {
			i32 left = i, rig = n, res = n;
			while( left <= rig ) {
				ci32 mid = ( left + rig ) >> 1;
				if( query_sum( i, mid ) > x ) {
					res = mid;
					rig = mid - 1;
				}
				else
					left = mid + 1;
			}
			if( query_sum( i, res ) > x ) 
				r[i] = res;
		}
		for( int i = n; i >= 1; i -- ) {
			if( r[i] == -1 )
				suf[i] = 0;
			else {
				if( r[i] + 1 <= n )
					suf[i] = 1 + suf[ r[i] + 1 ];
				else
					suf[i] = 1;
			}
		}
		i64 res = 0;
		for( int i = 1; i <= n; i ++ ) {
			res += ( n - i - suf[i] + 1 );
		}
		printf( "%lld\n", res );
	}
}
