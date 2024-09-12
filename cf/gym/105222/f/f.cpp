/*
 * f.cpp 2024-09-11
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
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	i64 T = read<i64>();
	while( T -- ) {
		ci64 x = read<i64>();
		ci64 y = read<i64>();
		ci64 r = read<i64>();
		ci64 vx = read<i64>();
		ci64 vy = read<i64>();

		ci64 lx = read<i64>() + r;
		ci64 ly = read<i64>() + r;
		ci64 rx = read<i64>() - r;
		ci64 ry = read<i64>() - r;

		if( lx > rx || ly > ry ) {
			printf( "No\n" );
			continue;
		}
		if( vx == 0 ) {
			if( lx <= x && x <= rx ) {
				if( ly <= y && y <= ry ) {
					printf( "Yes\n" );
					continue;
				}
				if( y <= ly ) {
					if( vy > 0 ) {
						printf( "Yes\n" );
						continue;
					}
					printf( "No\n" );
					continue;
				}
				else {
					if( vy < 0 ) {
						printf( "Yes\n" );
						continue;
					}
					printf( "No\n" );
					continue;
				}
			}
			else {
				printf( "No\n" );
				continue;
			}
		}
		else if( vy == 0 ) {
			if( ly <= y && y <= ry ) {
				if( lx <= x && x <= rx ) {
					printf( "Yes\n" );
					continue;
				}
				if( x <= lx ) {
					if( vx > 0 ) {
						printf( "Yes\n" );
						continue;
					}
					printf( "No\n" );
					continue;
				}
				else {
					if( vx < 0 ) {
						printf( "Yes\n" );
						continue;
					}
					printf( "No\n" );
					continue;
				}
			}
			else {
				printf( "No\n" );
				continue;
			}
		}
		else {
			ci64 clx = ( vy < 0 )? rx: lx;
			ci64 crx = ( vy < 0 )? lx: rx;
			ci64 cly = ( vx < 0 )? ry: ly;
			ci64 cry = ( vx < 0 )? ly: ry;
			const auto sgn = [&] ( ci64 cur ) { return cur < 0? 1: -1; }; 
			if( ( ( ly - y == 0 ) || sgn( ly - y ) == sgn(vy) ) && clx * vy <= ( ly - y ) * vx + x * vy &&
					( ly - y ) * vx + x * vy <= crx * vy ) {
				printf( "Yes\n" );
				continue;
			}
			if( ( ( ry - y == 0 ) || sgn( ry - y ) == sgn(vy) ) && clx * vy <= ( ry - y ) * vx + x * vy &&
					( ry - y ) * vx + x * vy <= crx * vy ) {
				printf( "Yes\n" );
				continue;
			}
			if( ( ( lx - x == 0 ) || sgn( lx - x ) == sgn(vx) ) && cly * vx <= ( lx - x ) * vy + y * vx &&
					( lx - x ) * vy + y * vx <= cry * vx ) {
				printf( "Yes\n" );
				continue;
			}
			if( ( ( rx - x == 0 ) || sgn( rx - x ) == sgn(vx) ) && cly * vx <= ( rx - x ) * vy + y * vx &&
					( rx - x )  * vy + y * vx <= cry * vx ) {
				printf( "Yes\n" );
				continue;
			}
		}
		printf( "No\n" );
	}
	return 0;
}
