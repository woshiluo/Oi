/*
 * c.cpp 2023-12-24
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

#include <map>
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

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 k = read<i32>();
		ci32 d = read<i32>();
		std::vector<i32> a( n + 1 );
		std::vector<std::pair<i32, i32>> la( n + 1 ), cur( n + 1 );
		std::vector<i32> v( k + 1 );
		std::vector<i32> pool( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<i32>();
		}
		for( int i = 1; i <= k; i ++ ) {
			v[i] = read<i32>();
		}

		int cnt = 0;
		for( int i = 1; i <= n; i ++ ) {
			if( a[i] == i ) 
				cnt ++;
		}
		int ans = cnt + ( d - 1 ) / 2;
		for( int i = 1; i <= Min( d - 1, Max( n, k ) * 2 ); i ++ ) {
			ci32 pos = v[ ( ( i - 1 ) % k ) + 1 ];
			for( int j = 1; j <= pos; j ++ ) {
				a[j] ++;
				if( a[j] == j ) {
					cnt ++;
				}
				if( a[j] == j + 1 ) {
					cnt --;
				}
			}
			chk_Max( ans, cnt + ( d - i - 1 ) / 2 );
		}
		printf( "%d\n", ans );
	}
}
