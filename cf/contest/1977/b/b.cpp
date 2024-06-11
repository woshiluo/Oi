/*
 * b.cpp 2024-05-26
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

int chk_pos( cu32 cur, ci32 pos ) { return ( cur >> pos ) & 1; }

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		u32 cur = read<i32>();
		int a[32];
		memset( a, 0, sizeof(a) );
		int p = 0;
		for( int k = 0; k <= 30; k ++ ) {
			if( !chk_pos( cur, k ) && p ) {
				cur |= 1u << k;
				p = false;
			}
			if( chk_pos( cur, k ) && p ) 
				continue;
			if( chk_pos( cur, k ) && chk_pos( cur, k + 1 ) ) {
				a[k] = -1;
				a[ k + 1 ] = 0;
				p = true;
				k ++;
				continue;
			}
			if( chk_pos( cur, k ) ) {
				a[k] = 1;
			}
		}
		if(p)
			a[31] = 1;
		printf( "32\n" );
		for( int i = 0; i < 32; i ++ ) {
			printf( "%d ", a[i] );
		}
		printf( "\n" );
	}
	
}
