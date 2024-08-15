/*
 * 6.cpp 2024-08-12
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

#include <functional>
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
	freopen( "6.in", "r", stdin );
	freopen( "6.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();

		ci32 max_item = m / ( n - 1 ) + 1;
		std::vector<std::vector<i32>> fa( max_item + 1, std::vector<i32>( n + 1 ) );

		for( int i = 0; i <= max_item; i ++ ) 
			for( int j = 0; j <= n; j ++ ) 
				fa[i][j] = j;

		const std::function<ci32(ci32, ci32)> get_fa = [&]( ci32 cur, ci32 k ) {
			if( fa[k][cur] == cur ) 
				return cur;
			fa[k][cur] = get_fa( fa[k][cur], k );
			return fa[k][cur];
		};

		std::vector<i32> ans( m + 1, -1 ), count( max_item + 1, 0 );
		for( int i = 1; i <= m; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			i32 left = 1, rig = max_item, res = -1;
			while( left <= rig ) {
				ci32 mid = ( left + rig ) >> 1;
				if( get_fa( u, mid ) == get_fa( v, mid ) ) {
					left = mid + 1;
				}
				else {
					res = mid;
					rig = mid - 1;
				}
			}

			if( res == -1 ) 
				continue;

			ans[i] = res;
			count[res] ++;
			fa[res][ get_fa( u, res ) ] = get_fa( v, res );
		}

		i32 max_valid = 0;
		for( int i = 1; i <= max_item; i ++ ) {
			if( count[i] == n - 1 ) 
				max_valid = i;
			else 
				break;
		}

		for( int i = 1; i <= m; i ++ ) {
			if( ans[i] <= max_valid ) 
				printf( "%d ", ans[i] );
			else
				printf( "-1 " );
		}
		printf( "\n" );
	}
}
