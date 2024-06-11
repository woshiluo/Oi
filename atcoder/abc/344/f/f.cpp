/*
 * f.cpp 2024-03-11
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

const int N = 82;
const i64 LLF = 0x3f3f3f3f3f3f3f3f;

i64 f[N][N][N][N], less[N][N][N][N];
i64 p[N][N], d[N][N], r[N][N];

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	i32 n = read<i32>();
	memset( f, 0x3f, sizeof(f) );
	f[1][1][1][1] = 0;

	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			p[i][j] = read<i32>();
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j < n; j ++ ) {
			r[i][j] = read<i32>();
		}
	}
	for( int i = 1; i < n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			d[i][j] = read<i32>();
		}
	}

	auto upper = [&]( i64 x, ci64 y ) {
		if( x < 0 ) 
			x = 0;
		return ( x / y ) + ( x % y != 0 );
	};
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			for( int p1 = 1; p1 <= i; p1 ++ ) {
				for( int p2 = 1; p2 <= j; p2 ++ ) {
					i32 cp1 = p1, cp2 = p2;
					if( p[i][j] >= p[cp1][cp2] )
						cp1 = i, cp2 = j;
					if( f[i][j][p1][p2] == LLF )
						continue;
					if( i + 1 <= n ) {
						ci64 times = upper( d[i][j] - less[i][j][p1][p2], p[cp1][cp2] );
						if( f[i + 1][j][cp1][cp2] > f[i][j][p1][p2] + times + 1 ) {
							f[i + 1][j][cp1][cp2] = f[i][j][p1][p2] + times + 1;
							less[i + 1][j][cp1][cp2] = less[i][j][p1][p2] + p[cp1][cp2] * times - d[i][j];
						}
						if( f[i + 1][j][cp1][cp2] == f[i][j][p1][p2] + times + 1 ) {
							chk_Max( less[i + 1][j][cp1][cp2], less[i][j][p1][p2] + p[cp1][cp2] * times - d[i][j] );
						}
					}

					if( j + 1 <= n ) {
						ci64 times = upper( r[i][j] - less[i][j][p1][p2], p[cp1][cp2] );
						if( f[i][j + 1][cp1][cp2] > f[i][j][p1][p2] + times + 1 ) {
							f[i][ j + 1 ][cp1][cp2] = f[i][j][p1][p2] + times + 1;
							less[i][j + 1][cp1][cp2] = less[i][j][p1][p2] + p[cp1][cp2] * times - r[i][j];
						}
						if( f[i][j + 1][cp1][cp2] == f[i][j][p1][p2] + times + 1 ) {
							chk_Max( less[i][j + 1][cp1][cp2], less[i][j][p1][p2] + p[cp1][cp2] * times - r[i][j] );
						}
					}
				}
			}
		}
	}

	i64 res = 1e18;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			chk_Min( res, f[n][n][i][j] );
		}
	}

	printf( "%lld\n", res );

}
