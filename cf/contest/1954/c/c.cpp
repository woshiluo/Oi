/*
 * c.cpp 2024-04-12
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

const int N = 110;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		static char buf[N];
		scanf( "%s", buf );
		ci32 n = strlen(buf);
		std::vector<i32> a, b;
		for( int i = 0; i < n; i ++ ) {
			a.push_back( buf[i] - '0' );
		}
		scanf( "%s", buf );
		for( int i = 0; i < n; i ++ ) {
			b.push_back( buf[i] - '0' );
		}
		// Ensure a >= b
		for( int i = 0; i < n; i ++ ) {
			if( a[i] == b[i] ) 
				continue;
			if( a[i] < b[i] )
				std::swap( a, b );
			break;
		}
		// Make two number close enough
		bool flag = false;
		for( int i = 0; i < n; i ++ ) {
			if( a[i] == b[i] ) 
				continue;
			if( !flag && a[i] > b[i] ) {
				flag = true;
				continue;
			}
			if( flag && a[i] > b[i] ) {
				std::swap( a[i], b[i] );
			}
		}

		for( auto &x: a ) 
			printf( "%d", x );
		printf( "\n" );
		for( auto &x: b ) 
			printf( "%d", x );
		printf( "\n" );
	}
	
}
