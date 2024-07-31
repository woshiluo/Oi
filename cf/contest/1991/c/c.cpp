/*
 * c.cpp 2024-07-28
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
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();

		std::vector<i32> a(n), cnt(2);
		for( auto &x: a ) {
			x = read<i32>();
			cnt[ x & 1 ] ++;
		}


		if( cnt[0] && cnt[1] ) {
			printf( "-1\n" );
			continue;
		}

		std::vector<i32> ops;
		for( int k = 0; ; k ++ ) {
			std::sort( a.begin(), a.end() );
			ci32 mid = ( a.front() + a.back() ) >> 1;
			if( mid == 0 ) {
				break;
			}
			ops.push_back(mid);
			for( auto &x: a )
				x = std::abs( x - mid );
		}

		if( ops.size() > 40 ) {
			printf( "-1\n" );
			continue;
		}
		else {
			printf( "%lu\n", ops.size() );
			for( auto &x: ops )
				printf( "%d ", x );
			printf( "\n" );
		}

	}
	
}
