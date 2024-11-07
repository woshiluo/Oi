/*
 * c.cpp 2024-10-30
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

enum Direction {
	West, 
	North,
	South,
	East,
};

Direction get_direction( const char cur ) {
	if( cur == 'W' )
		return West;
	if( cur == 'N' )
		return North;
	if( cur == 'S' ) 
		return South;
	if( cur == 'E' )
		return East;
	return North;
}

char get_char( Direction dir ) {
	if( dir == West ) 
		return 'W';
	if( dir == North ) 
		return 'N';
	if( dir == South ) 
		return 'S';
	if( dir == East ) 
		return 'E';
	return ' ';
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<std::pair<Direction, int>> list;
		for( int i = 1; i <= n; i ++ ) {
			static char buf[16];
			scanf( "%s", buf );
			ci32 s = read<i32>();
			list.emplace_back( get_direction( buf[0] ), s );
		}
		Direction cur = list[0].first;
		bool first = true;
		std::vector<std::pair<i32, i32>> res;
		// 0 left
		// 1 rig
		// 2 straight
		for( auto &[ dir, t ]: list ) {
			if( !first ) {
				if( dir == cur ) {
					continue;
				}
				if( cur == North ) {
					if( dir == West ) 
						res.emplace_back( 0, 0 );
					else 
						res.emplace_back( 1, 0 );
				}
				if( cur == South ) {
					if( dir == East ) 
						res.emplace_back( 0, 0 );
					else 
						res.emplace_back( 1, 0 );
				}
				if( cur == West ) {
					if( dir == South ) 
						res.emplace_back( 0, 0 );
					else 
						res.emplace_back( 1, 0 );
				}
				if( cur == East ) {
					if( dir == North ) 
						res.emplace_back( 0, 0 );
					else 
						res.emplace_back( 1, 0 );
				}
			}
			cur = dir;
			first = false;
			res.emplace_back( 2, t );
		}
		printf( "%zu %c\n", res.size(), get_char(list[0].first) );
		for( auto &[a, b]: res ) {
			if( a == 0 ) 
				printf( "L\n" );
			if( a == 1 ) 
				printf( "R\n" );
			if( a == 2 ) 
				printf( "Z %d\n", b );
		}
	}
}
