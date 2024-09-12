/*
 * e.cpp 2024-09-11
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

int cnt[N][N][4];
// 0 up
// 1 left
// 2 rig
// 3 down
char str[N][N];

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				for( int k = 0; k < 4; k ++ )
					cnt[i][j][k] = 0;
			}
		}
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%s", str[i] + 1 );
		}
		if( str[1][m] != '.' ) {
			printf( "No\n" );
			continue;
		}
		const auto check = [&]( ci32 x, ci32 y ) {
			if( x <= 0 || y <= 0 || x > n || y > m ) 
				return false;
			return ( str[x][y] == 'C' );
		};
		bool flag = true;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				if( str[i][j] == 'C' || str[i][j] == '.' ) 
					continue;
				if( str[i][j] == 'U' ) {
					if( check( i - 1, j ) ) 
						cnt[ i - 1 ][j][3] ++;
					else 
						flag = false;
				}
				if( str[i][j] == 'D' ) {
					if( check( i + 1, j ) ) 
						cnt[ i + 1 ][j][0] ++;
					else 
						flag = false;
				}
				if( str[i][j] == 'L' ) {
					if( check( i, j - 1 ) ) 
						cnt[i][ j - 1 ][2] ++;
					else 
						flag = false;
				}
				if( str[i][j] == 'R' ) {
					if( check( i, j + 1 ) ) 
						cnt[i][ j + 1 ][1] ++;
					else 
						flag = false;
				}
			}
		}
		for( int i = 1; i <= n; i ++ )
			for( int j = 1; j <= m; j ++ ) {
				if( str[i][j] != '.' )
					continue;
				if( i == 1 && j == m )
					continue;
				else
					flag = false;
			}
		if( !flag ) {
			printf( "No\n" );
			continue;
		}

		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				if( str[i][j] == 'C' ) {
					if( cnt[i][j][0] && cnt[i][j][3] )
						flag = false;
					if( cnt[i][j][1] && cnt[i][j][2] )
						flag = false;
					i32 total = 0;
					for( int k = 0; k < 4; k ++ ) {
						if( cnt[i][j][k] > 1 ) 
							flag = false;
						total += cnt[i][j][k];
					}
					if( total != 2 ) 
						flag = false;
				}
			}
		}
		if( !flag ) 
			printf( "No\n" );
		else 
			printf( "Yes\n" );
	}
}
