/*
 * c.cpp 2023-11-03
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
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

const i32 N = 50;

i32 f[N][N][N][N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 n = read<i32>();
	i64 ans = 0;

	for( i32 o = 1; o <= n; o ++ ) {
		static char readin[8];
		static i32 nums[8];
		scanf( "%s", readin );

		ci32 len = strlen(readin);
		i32 sum = 0;
		for( int i = 0; i < len; i ++ ) {
			nums[i] = readin[i] - '0';
			sum += nums[i];
		}
		{
			i32 res = 0;
			for( int i = 0; i <= len; i ++ )  {
				f[len][i][res][ sum - res ] ++;
				if( i < len )
					res += nums[i];
			}
		}
	}

	for( int i = 1; i <= 5; i ++ ) {
		for( int j = 1; j <= 5; j ++ ) {
			if( ( i + j ) & 1 ) 
				continue;
			ci32 k = ( ( i + j ) >> 1 );
			for( int p1 = 0; p1 < N; p1 ++ ) {
				for( int p2 = p1; p2 < N; p2 ++ ) {
					if( i < j ) {
						ans += 1LL * f[i][0][0][ p2 - p1 ] * f[j][ k - i ][p1][p2];
					}
					else {
						ans += 1LL * f[i][ i - k + j ][p2][p1] * f[j][0][0][p2 - p1];
					}
				}
			}
		}
	}
//	for( int i = 1; i <= 5; i ++ ) {
//		for( int p2 = 0; p2 < N; p2 ++ ) {
//			ans += 1LL * f[i][0][0][p2] * f[i][0][0][p2];
//		}
//	}
	printf( "%lld\n", 1LL * ans );
}
