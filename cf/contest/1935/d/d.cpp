/*
 * d.cpp 2024-03-05
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
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 c = read<i32>();
		std::vector<i32> s(n);
		i32 odd_cnt = 0, even_cnt = 0;
		for( auto &x: s ) {
			x = read<i32>();
			if( x & 1 )
				odd_cnt ++;
			else 
				even_cnt ++;
		}
		i64 res = 1LL * ( c + 1 ) * c / 2LL + c + 1; 
		// sum as x
		for( auto &x: s ) {
			res -= ( x >> 1 ) + 1;
			// 0 ( 0, 0 )
			// 1 ( 0, 1 )
			// 2 ( 0, 2 ) ( 1, 1 )
			// 3 ( 0, 3 ) ( 1, 2 )
		}
		// sub as x
		for( auto &x: s ) {
			res -= c - x + 1;
		}

		// sum as x and sub as x
		res += 1LL * odd_cnt * ( odd_cnt - 1 ) / 2LL + odd_cnt;
		res += 1LL * even_cnt * ( even_cnt - 1 ) / 2LL + even_cnt;
		printf( "%lld\n", res );
	}
}
