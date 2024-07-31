/*
 * e.cpp 2024-07-29
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

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		ci32 hp = read<i32>();
		ci32 dmg = read<i32>();

		ci32 st = hp - dmg;
		std::vector<i32> blocked(m);
		std::vector<char> cur(m);
		for( int i = ( st % m ), j = 0; j < dmg && j < m; i = ( i + 1 ) % m, j ++ ) {
			blocked[i] = true;
		}

		ci32 less = hp - dmg - 1;
		for( int i = 0; i < m; i ++ ) {
			if( blocked[i] ) 
				cur[i] = '.';
			else {
				if( less < m && i > less ) {
					cur[i] = ' ';
					continue;
				}
				ci32 base = ( ( less ) / m ) - 1;
				if( ( less % m ) < i ) {
					cur[i] = ( base % 5 ) + 'A';
				}
				else {
					cur[i] = ( ( base + 1 ) % 5 ) + 'A';
				}
			}

		}
		printf( "+" );
		for( int i = 1; i <= m; i ++ ) 
			printf( "-" );
		printf( "+" );
		printf("\n");

		for( int j = 0; j < n; j ++ ) {
			printf( "|" );
			for( int i = 0; i < m; i ++ ) {
				printf( "%c", cur[i] );
			}
			printf( "|" );
			printf( "\n" );
		}

		printf( "+" );
		for( int i = 1; i <= m; i ++ ) 
			printf( "-" );
		printf( "+" );
		printf("\n");

	}
	
}
