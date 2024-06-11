/*
 * d.cpp 2024-03-01
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
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> a( n + 2 ), pre( n + 2 ), nxt( n + 2 );
		std::vector<i64> sum( n + 2 );
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<i32>();
			sum[i] = sum[ i - 1 ] + a[i];
		}
		{
			int la = 0;
			for( int i = 1; i <= n; i ++ ) {
				if( a[ i - 1 ] != a[i] ) 
					la = i - 1;
				pre[i] = la;
			}
		}
		{
			i32 nt = n + 1;
			nxt[ n + 1 ] = n + 1;
			for( int i = n; i >= 1; i -- ) {
				if( a[ i + 1 ] != a[i] ) 
					nt = i + 1;
				nxt[i] = nt;
			}
		}
		for( int i = 1; i <= n; i ++ ) {
			i32 ans = -1;
			if( pre[ i - 1 ] != 0 ) {
				i32 left = 1, rig = pre[ i - 1 ], res = -1;
				while( left <= rig ) {
					ci32 mid = ( left + rig ) >> 1;
					if( sum[ i - 1 ] - sum[ mid - 1 ] > a[i] ) {
						res = mid;
						left = mid + 1;
					}
					else {
						rig = mid - 1;
					}
				}
				if( res != -1 ) {
					i32 time = i - res;
					if( ans == -1 || time < ans ) 
						ans = time;
				}
			}
			if( nxt[ i + 1 ] != n + 1 ) {
				i32 left = nxt[ i + 1 ], rig = n, res = -1;
				while( left <= rig ) {
					ci32 mid = ( left + rig ) >> 1;
					if( sum[mid] - sum[i] > a[i] ) {
						res = mid;
						rig = mid - 1;
					}
					else {
						left = mid + 1;
					}
				}
				if( res != -1 ) {
					i32 time = res - i;
					if( ans == -1 || time < ans ) 
						ans = time;
				}
			}
			if( a[ i + 1 ] > a[i] || a[ i - 1 ] > a[i] ) 
				ans = 1;
			printf( "%d ", ans );
		}
		printf( "\n" );
	}
}
