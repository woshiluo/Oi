/*
 * a.cpp 2024-11-06
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
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ( ch - '0' );
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

const int N = 5e5 + 1e4;

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		static char buf[N];
		scanf( "%s", buf );
		ci32 len = strlen(buf);
		std::vector<std::pair<bool, i32>> list;
		for( int i = 0; i < len; i ++ ) {
			bool cur = ( buf[i] == '>' );
			if( list.empty() || list.back().first != cur ) 
				list.emplace_back( cur, 1 );
			else 
				list.back().second ++;
		}
		if( list.size() >= 3 && list[0].first == true && list.back().first == true && list.back().second >= 3 ) {
			std::vector<std::pair<i32, i32>> res;
			i32 end = len;
			res.emplace_back( 1, end );
			for( int i = 3; i < list.back().second; i ++ ) {
				end --;
				res.emplace_back( 1, end );
			}
			for( int i = 1; i < end - 3; i ++ ) {
				if( buf[i] == '>' ) 
					res.emplace_back( i + 1, end );
			}
			printf( "Yes %zu\n", res.size() );
			for( auto &[l, r]: res ) {
				printf( "%d %d\n", l, r - l + 1 );
			}
		}
		else 
			printf( "No\n" );
	}
	return 0;
}
