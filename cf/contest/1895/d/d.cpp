/*
 * d.cpp 2023-11-03
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

constexpr i32 full_pow( i32 cur ) { return 1 << cur; }
constexpr bool chk_pos( i32 cur, i32 pos ) { return cur & full_pow(pos); }

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = 1;
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> a( n );
		for( int i = 1; i < n; i ++ ) {
			a[i] = read<i32>();
		}
		std::vector<i32> res( n + 1 );
		for( int i = 0; i < 31; i ++ ) {
			std::vector<i32> count(2), count_b(2), cur_b( n + 1 );
			for( int j = 0; j < n; j ++ ) {
				count[ chk_pos( j, i ) ] ++;
			}
			cur_b[1] = 1;
			for( int j = 2; j <= n; j ++ ) {
				cur_b[j] = cur_b[ j - 1 ] ^ ( chk_pos( a[ j - 1 ], i ) );
			}
			for( int j = 1; j <= n; j ++ )
				count_b[ cur_b[j] ] ++;
			bool flag = ( count != count_b );
			for( int j = 1; j <= n; j ++ ) {
				res[j] += ( flag ^ cur_b[j] ) * full_pow(i);
			}
		}
		for( int i = 1; i <= n; i ++ ) 
			printf( "%d ", res[i] );
		printf( "\n" );
	}
}
