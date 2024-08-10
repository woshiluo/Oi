/*
 * e.cpp 2024-08-08
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

const int BLOCK = 1e6;
const int MAXN = 1e6 + 5;

i32 buf[MAXN];

constexpr inline i64 get_s( i64 cur ) {
	i32 res = 0;
	while( cur ) {
		res += ( cur % 10 );
		cur /= 10;
	}
	return res;
}

constexpr inline i64 fast_get_s( const i64 cur ) {
	return buf[ cur % BLOCK ] + buf[ cur / BLOCK ];
}

i64 list[MAXN];
i32 lp = 0;

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	for( int i = 0; i < MAXN; i ++ ) {
		buf[i] = get_s(i);
	}

	i32 T = read<i32>();
	while( T -- ) {
		lp = 0;
		ci64 n = read<i64>();
		for( i64 i = Max( (i64)1, n - 110 ); i <= n; i ++ ) {
			if( ( n % i ) == fast_get_s(i) ) {
				list[lp] = i;
				lp ++;
			}
		}
		for( i64 i = 1; i * i <= n; i ++ ) {
			if( ( n % i ) == fast_get_s(i) ) {
				list[lp] = i;
				lp ++;
			}
			if( n / i == i ) 
				continue;
			ci64 p = n / i;
			ci64 diff = ( 110 / i ) + 1;
			for( i64 pp = Max( (i64)1, p - diff ); pp <= p; pp ++ ) {
				if( ( n % pp ) == fast_get_s(pp) ) {
					list[lp] = pp;
					lp ++;
				}
			}
		}
		std::sort( list, list + lp );
		ci32 size = std::unique( list, list + lp ) - list;
		// list.erase( std::unique( list.begin(), list.end() ), list.end() );
		printf( "%d\n", size );
	}

}
