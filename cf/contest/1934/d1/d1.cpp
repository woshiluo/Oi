/*
 * d1.cpp 2024-03-02
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
	freopen( "d1.in", "r", stdin );
	freopen( "d1.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci64 n = read<i64>();
		ci64 m = read<i64>();
		int k = 0;
		for( ; ( 1LL << k ) <= n; k ++ );
		k -= 2;
		for( ; ( k >= 0 ) && ( ( n >> k ) & 1 ) == 0; k -- );
		i64 max = ( 1LL << ( k + 1 ) ) - 1;
		if( m < n && ( n ^ m ) < n ) {
			printf( "1\n" );
			printf( "%lld %lld\n", n, m );
		}
		else if( m > max ) 
			printf( "-1\n" );
		else {
			printf( "%d\n", max == m? 1: 2 );
			printf( "%lld %lld", n, max );
			if( max != m ) 
				printf( " %lld", m );
			printf( "\n" );
		}
	}
	
}
