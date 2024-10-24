/*
 * f.cpp 2024-10-23
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

#include <set>
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
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ( ch - '0' );
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

const int N = 1100;

bool vis[N][N];
bool has_hard[N][N];

int gcd( ci32 a, ci32 b ) { return b? gcd( b, a % b ): a; }

std::set<double> soft_x[N], soft_y[N];

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	for( int i = 1; i <= n; i ++ ) {
		i32 x1 = read<i32>();
		i32 y1 = read<i32>();
		i32 x2 = read<i32>();
		i32 y2 = read<i32>();
		if( y1 == y2 ) {
			for( int x = Min( x1, x2 ); i <= Max( x1, x2 ); i ++ ) {
				has_hard[x][y1] = true;
			}
		}
		else if( x1 == x2 ) {
			for( int y = Min( y1, y2 ); i <= Max( y1, y2 ); i ++ ) {
				has_hard[x1][y] = true;
			}
		}
		else {
			// Block on non-int
			for( int i = Min( x1, x2 ); i <= Max( x1, x2 ); i ++ ) {
				const int p1 = ( i - x2 ) * y1 - y2;
				const int p2 = ( x1 - x2 );
				const double y = (double)p1 / (double)p2 + y2;
				if( p1 % p2 == 0 ) {
					has_hard[i][ p1 / p2 + y2 ] = true;
				}
				soft_x[i].insert(y);
			}
			for( int i = Min( y1, y2 ); i <= Max( y1, y2 ); i ++ ) {
				const int p1 = ( i - y2 ) * ( x1 - x2 );
				const int p2 = ( y1 - y2 );
				if( p1 % p2 == 0 ) {
					has_hard[ p1 / p2 + x2 ][i] = true;
				}
				const double x = (double)p1 / (double)p2 + x2;
				soft_y[i].insert(x);
			}
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			if( !vis[
		}
	}
	
}
