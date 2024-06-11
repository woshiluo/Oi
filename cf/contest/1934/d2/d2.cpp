/*
 * d2.cpp 2024-03-02
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cassert>
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

void first() {
	printf( "first\n" );
	fflush(stdout);
}

void second() {
	printf( "second\n" );
	fflush(stdout);
}

void print( ci64 x, ci64 y ) {
	printf( "%lld %lld\n", x, y );
	fflush(stdout);
}

int main() {
#ifdef woshiluo
//	freopen( "d2.in", "r", stdin );
//	freopen( "d2.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		i64 n = read<i64>();
		i64 k = __builtin_popcountll(n);
		if( k & 1 ) {
			second();
		}
		else {
			first();
		}
		while(1) {
			k =  __builtin_popcountll(n);
			if( k & 1 ) {
				ci64 x = read<i64>();
				ci64 y = read<i64>();
				if( x == 0 ) {
					break;
				}
				assert( x > 0 && y > 0 );
				if( __builtin_popcountll(x) & 1 ) 
					n = y;
				else 
					n = x;
			}
			else {
				int m = 1;
				for( ; ( 1LL << m ) <= n; m ++ );
				i64 p = ( 1LL << ( m - 1 ) );
				n ^= p;
				print( n, p );
			}
		}
	}
}
