/*
 * c.cpp 2024-08-06
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


void shell_sort(int length) {
	int h = 1;
	while (h < length / 3) {
		h = 3 * h + 1;
	}
	int cnt = 0;
	while (h >= 1) {
		std::set<i32> s1, s2;
		for (int i = h; i < length; i++) {
			for (int j = h + 1; j <= length; j ++) {
//				if( s1.count( j - h ) ) {
//					s2.insert(j);
//				}
//				else {
//					s1.insert(j);
//				}
			}
			cnt += 2;
//			printf( "%zu ", s1.size() );
//			for( auto &x: s1 ) 
//				printf( "%d %d ", x - h, x );
//			printf( "\n" );
//			for( auto &x: s2 ) 
//				printf( "%d %d ", x - h, x );
//			printf( "\n" );
//			fprintf( stderr, "%d %d\n", h );
//			fflush(stderr);
		}
		h = h / 3;
	}
	printf( "%d\n", cnt );
}


int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	shell_sort(10000);
}
