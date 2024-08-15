/*
 * a.cpp 2024-08-13
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

const int N = 512;

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();
	i32 l, r, t, b;
	l = m, r = 0, t = n, b = 0;
	for( int i = 1; i <= n; i ++ ) {
		static char buf[N];
		scanf( "%s", buf + 1 );
		bool flag = false;
		for( int j = 1; j <= m; j ++ ) {
			if( buf[j] == 'x' ) {
				flag = true;
				chk_Max( r, j );
				chk_Min( l, j );
			}
		}
		if( flag ) {
			chk_Min( t, i );
			chk_Max( b, i );
		}
	}

	ci32 p = r - l + 1, q = b - t + 1;
	ci32 d = std::__gcd( p, q );
	for( int i = 1; i <= q / d; i ++ ) {
		for( int j = 1; j <= p / d; j ++ ) {
			printf( "x" );
		}
		printf( "\n" );
	}
	
}
