/*
 * c.cpp 2024-03-02
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

i32 query( ci32 x, ci32 y ) {
	printf( "? %d %d\n", x, y );
	fflush(stdout);
	ci32 res = read<i32>();
	return res;
}

void answer( ci32 x, ci32 y ) {
	printf( "! %d %d\n", x, y );
	fflush(stdout);
}


int main() {
#ifdef woshiluo
//	freopen( "c.in", "r", stdin );
//	freopen( "c.out", "w", stdout );
#endif
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();

		ci32 p1 = query( 1, 1 );
		ci32 p2 = query( n, 1 );
		ci32 p3 = query( 1, m );

		ci32 y1 = ( ( ( p1 - p3 ) + ( m - 1 ) ) / 2 ) + 1;
		ci32 x1 = p1 - ( y1 - 1 ) + 1;
		ci32 x2 = ( ( ( p1 - p2 ) + ( n - 1 ) ) / 2 ) + 1;
		ci32 y2 = p1 - ( x2 - 1 ) + 1;
		if( x1 >= 1 && x1 <= n && y1 >= 1 && y1 <= m ) {
			ci32 d = query( x1, y1 );
			if( d == 0 ) {
				answer( x1, y1 );
				continue;
			}
		}
		answer( x2, y2 );
	}
	
}
