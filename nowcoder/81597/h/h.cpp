/*
 * h.cpp 2024-07-18
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

#include <map>
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

const int N = 2e5 + 1e4;

int main() {
#ifdef woshiluo
	freopen( "h.in", "r", stdin );
	freopen( "h.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 x = read<i32>();
	ci32 y = read<i32>();

	static char buf[N];
	scanf( "%s", buf + 1 );

	if( x == 0 && y == 0 ) {
		printf( "%lld\n", 1LL * n * ( n + 1 ) / 2LL );
		return 0;
	}

	std::vector<std::pair<i32, i32>> sum;
	sum.push_back( std::make_pair( 0, 0 ) );
	for( int i = 1; i <= n; i ++ ) {
		auto [ px, py ] = sum.back();
		if( buf[i] == 'W' ) 
			sum.push_back( std::make_pair( px, py + 1 ) );
		if( buf[i] == 'A' ) 
			sum.push_back( std::make_pair( px - 1, py ) );
		if( buf[i] == 'S' ) 
			sum.push_back( std::make_pair( px, py - 1 ) );
		if( buf[i] == 'D' ) 
			sum.push_back( std::make_pair( px + 1, py ) );
	}

	i64 res = 0;
	std::map< std::pair<i32, i32>, i32 > map;
	for( int i = n; i >= 0; i -- ) {
		auto [ cx, cy ] = sum[i];
		const auto nxt = std::make_pair( cx + x, cy + y );
		if( map.count( nxt ) ) {
			res += n - map[nxt] + 1;
		}
		map[ sum[i] ] = i;
	}
	printf( "%lld\n", res );
}
