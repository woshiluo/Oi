/*
 * e.cpp 2024-06-06
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

template <class T>
T aabs( T cur ){ return cur < 0? -cur: cur; }

void work() {
	ci32 n = read<i32>();
	ci32 m = read<i32>();
	struct Node { int id; int x, y; };
	std::vector<Node> list;
	for( int i = 1; i <= n; i ++ ) {
		ci32 x = read<i32>();
		ci32 y = read<i32>();
		list.push_back( (Node){ i - 1, x + y, x - y } );
	}

	{
		std::map<i32, std::map<i32, i32>> mp;
		std::map<i32, std::map<i32, i32>> lp;
		for( auto &[id, x, y]: list ) {
			mp[x][y] = id;
		}
		for( auto &[id, x, y]: list ) {
			if( mp[x].count( y + m ) ) 
				lp[x][y] = id;
		}
		for( auto &[id, x, y]: list ) {
			{ 
				auto p = lp[ x - m ].lower_bound( y - m );
				if( p != lp[ x - m ].end() && list[ p -> second ].y <= y ) {
					printf( "%d %d %d\n", id + 1, p -> second + 1, mp[ x - m ][ list[ p -> second ].y + m ] + 1 );
					return ;
				}
			}
			{ 
				auto p = lp[ x + m ].lower_bound( y - m );
				if( p != lp[ x + m ].end() && list[ p -> second ].y <= y ) {
					printf( "%d %d %d\n", id + 1, p -> second + 1, mp[ x + m ][ list[ p -> second ].y + m ] + 1 );
					return ;
				}
			}
		}
	}
	{
		std::map<i32, std::map<i32, i32>> mp;
		std::map<i32, std::map<i32, i32>> lp;
		for( auto &[id, x, y]: list ) {
			mp[x][y] = id;
		}
		for( auto &[id, x, y]: list ) {
			if( mp[ x + m ].count(y) ) 
				lp[y][x] = id;
		}
		for( auto &[id, x, y]: list ) {
			{ 
				auto p = lp[ y - m ].lower_bound( x - m );
				if( p != lp[ y - m ].end() && list[ p -> second ].x <= x ) {
					printf( "%d %d %d\n", id + 1, p -> second + 1, mp[ list[ p -> second ].x + m ][ y - m ] + 1 );
					return ;
				}
			}
			{ 
				auto p = lp[ y + m ].lower_bound( x - m );
				if( p != lp[ y + m ].end() && list[ p -> second ].x <= x ) {
					printf( "%d %d %d\n", id + 1, p -> second + 1, mp[ list[ p -> second ].x + m ][ y + m ] + 1 );
					return ;
				}
			}
		}
	}
	printf( "0 0 0\n" );
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	i32 T = read<i32>();
	while( T -- ) {
		work();
	}
}
