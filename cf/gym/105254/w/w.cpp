/*
 * w.cpp 2024-10-01
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
#include <tuple>
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

i32 query( ci32 a, ci32 b, ci32 c ) {
	printf( "%d %d %d\n", a, b, c );
	fflush(stdout);
	ci32 res = read<i32>();
	return res;
}

int main() {
#ifdef woshiluo
//	freopen( "w.in", "r", stdin );
//	freopen( "w.out", "w", stdout );
#endif


	ci32 r1 = query( 1, 0, 0 );
	ci32 r2 = query( 0, 1, 0 );
	ci32 r3 = query( 0, 0, 1 );
	ci32 r4 = query( 1, 1, 1 );
	if( r4 == r1 + r2 + r3 ) {
		ci32 r5 = query( 2, 3, 4 );
		printf( "%d %d %d\n", r1, r2, r3 );
	}
	else {
		ci32 r5 = query( 2, 3, 4 );
		if( r5 == 2 * r1 + 3 * r2 + 4 * r3 ) {
			printf( "%d %d %d\n", r1, r2, r3 );
		}
		else {
			std::map<std::tuple<i32, i32, i32>, i32> mp;
			{
				// Assume r1 is correct
				ci32 ar4 = r4 - r1; // b + c
				ci32 ar5 = r5 - 2 * r1; // 3b + 4c
				ci32 c = ar5 - 3 * ar4;
				ci32 b = ar4 - c;
				mp[ std::make_tuple( r1, b , c ) ] ++;
			}
			{
				// Assume r2 is correct
				ci32 br4 = r4 - r2; // a + c
				ci32 br5 = ( r5 - 3 * r2 ) / 2; // 2a + 4c -> a + 2c
				ci32 c = br5 - br4;
				ci32 a = br4 - c;
				mp[ std::make_tuple( a, r2 , c ) ] ++;
			}
			{
				// Assume r3 is correct
				ci32 cr4 = r4 - r3; // a + b
				ci32 cr5 = ( r5 - 4 * r3 ); // 2a + 3b
				ci32 b = cr5 - 2 * cr4;
				ci32 a = cr4 - b;
				mp[ std::make_tuple( a, b, r3 ) ] ++;
			}
			for( auto &[t, cnt]: mp ) {
				if( cnt >= 2 ) {
					const auto &[a, b, c] = t;
					printf( "%d %d %d\n", a, b, c );
				}
			}
		}
	}
	fflush(stdout);
	return 0;
}
