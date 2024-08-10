/*
 * 3.cpp 2024-08-05
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

#include <set>
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

const int N = 1e5 + 1e4;

/// 0 top y + 1
/// 1 left
/// 2 rig x + 1
/// 3 bottom

int left[4] = { 1, 3, 0, 2 };
int rig[4] = { 2, 0, 3, 1 };

int dx[4] = { 0, -1, 1, 0 };
int dy[4] = { 1, 0, 0, -1 };

int main() {
#ifdef woshiluo
	freopen( "3.in", "r", stdin );
	freopen( "3.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		static char buf[N];
		scanf( "%s", buf + 1 );
		i32 dir = 0, cx = 0, cy = 0;

		std::set<std::pair<i32, i32>> set;
		set.insert( std::make_pair( 0, 0 ) );
		bool cross = false;
		for( int i = 1; i <= n; i ++ ) {
			if( buf[i] == 'L' ) 
				dir = left[dir];
			if( buf[i] == 'R' ) 
				dir = rig[dir];
			cx += dx[dir];
			cy += dy[dir];
			if( i == n ) {
				break;
			}
			if( set.count( std::make_pair( cx, cy ) ) )
				cross = true;
			set.insert( std::make_pair( cx, cy ) );
		}

		if( cross ) 
			printf( "-1" );
		else {
			if( cx == 0 && cy == 0 ) {
				if( dir == 0 ) 
					printf( "1" );
				else 
					printf( "0" );
			}
			else {
				printf( "0" );
			}
		}
		printf( "\n" );
	}
}
