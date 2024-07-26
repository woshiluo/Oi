/*
 * c.cpp 2024-07-09
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

	ci32 n = read<i32>();
	ci64 t = read<i32>();
	std::vector<i32> h(n);
	for( auto &x: h ) 
		x = read<i32>();
	i64 la_fi_1 = 0, la_gap = 0;
	for( int i = 0; i < n; i ++ ) {
		if( la_gap == 0 ) {
			la_fi_1 = h[i];
			la_gap = h[i];
			ci64 p = t / h[i] + 1;
			printf( "%lld\n", p );
			continue;
		}
		if( t - la_fi_1 <= 0 ) {
			printf( "1\n" );
			continue;
		}
		if( h[i] >= la_gap ) {
			ci64 p = ( t - la_fi_1 ) / h[i] + 1;
			printf( "%lld\n", p );
			la_gap = h[i];
		}
		else {
			ci64 p = ( t - la_fi_1 ) / la_gap + 1;
			if( la_fi_1 + ( p - 1 ) * la_gap + h[i] <= t )
				printf( "%lld\n", p + 1 );
			else
				printf( "%lld\n", p );
		}

		la_fi_1 += h[i];
	}
}
