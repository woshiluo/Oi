/*
 * c.cpp 2024-07-06
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
		ci32 n =read<i32>();
		std::vector<std::pair<i32, i32>> list(n);
		for( auto &[x,y]: list ) {
			x = read<i32>();
		}
		for( auto &[x,y]: list ) {
			y = read<i32>();
		}
		int a = 0, b = 0;
		int both1_cnt = 0;
		int bothn1_cnt = 0;
		for( auto [x, y]: list ) {
			if( x == -1 && y == -1 ) 
				bothn1_cnt ++;

			if( x == 1 && y == -1 ) 
				a ++;
			if( x == -1 && y == 1 )
				b ++;

			if( x == 1 && y == 0 )
				a ++;
			if( x == 0 && y == 1 ) 
				b ++;

			if( x == 1 && y == 1 ) 
				both1_cnt ++;
		}
		for( int i = 0; i < bothn1_cnt; i ++ ) {
			if( a < b ) 
				b --;
			else 
				a --;
		}
		for( int i = 0; i < both1_cnt; i ++ ) {
			if( a < b ) 
				a ++;
			else 
				b ++;
		}
		printf( "%d\n", Min( a, b ) );
	}
	
}
