/*
 * a.cpp 2023-11-19
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

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 k = read<i32>();
		static char str[110];
		scanf( "%s", str );
		int cur_b = 0;
		for( int i = 0; i < n; i ++ ) {
			cur_b += str[i] == 'B';
		}
		if( cur_b == k ) {
			printf( "0\n" );
		}
		else if( cur_b > k ) {
			int d = cur_b - k;
			for( int i = 0; i < n; i ++ ) {
				if( str[i] == 'B' ) 
					d --;
				if( d == 0 ) {
					printf( "1\n%d A\n", i + 1 );
					break;
				}
			}
		}
		else {
			int d = k - cur_b;
			for( int i = 0; i < n; i ++ ) {
				if( str[i] == 'A' ) 
					d --;
				if( d == 0 ) {
					printf( "1\n%d B\n", i + 1 );
					break;
				}
			}
		}
	}
}
