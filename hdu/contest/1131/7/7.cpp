/*
 * 7.cpp 2024-08-12
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
#include <cinttypes>

#include <random>
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


u64 add( cu64 p, cu64 q, ci32 k ) {
	u64 res = 0;
	for( __int128 offset = 1; offset * k < UINT64_MAX; offset *= k ) {
		cu64 p1 = ( p / offset ) % k;
		cu64 p2 = ( q / offset ) % k;
		res += ( ( p1 + p2 ) % k ) * offset;
	}
	return res;
}


const int LIM = 4e4 + 1;

std::random_device seed;
std::mt19937 rnd(seed());

int main() {
#ifdef woshiluo
	freopen( "7.in", "r", stdin );
	freopen( "7.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci64 a = read<i64>();
		ci64 b = read<i64>();
		ci64 c = read<i64>();

		ci64 d = a + b - c;

		if( d < 0 ) {
			printf( "0\n" );
			continue;
		}
		if( d == 0 ) {
			printf( "-1\n" );
			continue;
		}

		i32 cnt = 0;
		for( int i = 2; i <= LIM; i ++ ) {
			if( add( a, b, i ) == c ) {
				cnt ++;
			}
		}
		for( int i = 1; 1LL * i * i <= d; i ++ ) {
			if( d % i != 0 ) 
				continue;
			if( i > LIM ) {
				if( add( a, b, i ) == c ) 
					cnt ++;
			}
			if( i == d / i ) 
				continue;
			if( d / i > LIM ) {
				if( add( a, b, d / i ) == c ) 
					cnt ++;
			}
		}

//		i32 cnt1 = 0;
//		for( int k = 2; k <= a + b; k ++ ) {
//			if( add( a, b, k ) == c ) 
//				cnt1 ++;
//
//		}
//		if( cnt != cnt1 ) {
//			printf( "%d %d %d\n", a, b, c );
//			fflush(stdout);
//			std::exit(-1);
//		}
		printf( "%d\n", cnt );
	} 
}
