/*
 * h.cpp 2024-10-02
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

i32 b[10];

int main() {
#ifdef woshiluo
	freopen( "h.in", "r", stdin );
	freopen( "h.out", "w", stdout );
#endif

	std::multiset<i32> set;

	ci32 n = read<i32>();
	ci32 a = read<i32>();
	ci32 k = read<i32>();
	ci32 p = read<i32>();

	i32 ca = a;
	b[0] = a;
	i32 b_size = 1;
	for( int i = 2; i <= n; i ++ ) {
		ca = ( 1LL * ca * k ) % p;
		bool flag = false;
		for( int j = 0; j < b_size; j ++ ) {
			if( b[j] > ca ) 
				continue;
			for( int o = b_size; o >= j + 1; o -- ) {
				b[o] = b[ o - 1 ];
			}
			flag = true;
			b_size ++;
			b[j] = ca;
			break;
		}
		if( !flag ) {
			b[b_size] = ca;
			b_size ++;
		}
		chk_Min( b_size, 5 );
	}
	for( int i = b_size - 1; i >= 0; i -- ) 
		printf( "%d ", b[i] );
}
