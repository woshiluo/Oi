/*
 * c.cpp 2023-12-28
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

template<class T>
T aabs( T cur ) { return cur < 0? -cur: cur; }

const int N = 1e5 + 1e4;

int a[N], sum[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	for( int i = 1; i <= n; i ++ ) 
		a[i] = read<i32>();
	std::sort( a + 1, a + n + 1 );
	for( int i = 1; i <= n; i ++ ) 
		sum[i] += sum[ i - 1 ] + a[i];

	if( n & 1 ) {
		ci32 half = n / 2;
		if( aabs( sum[n] - sum[half] - sum[half] ) > aabs( sum[n] - sum[ half + 1 ] - sum[ half + 1 ] ) ) {
			printf( "Outgoing #: %d\n", n - half );
			printf( "Introverted #: %d\n", half );
			printf( "Diff = %d\n", aabs( sum[n] - sum[half] - sum[half] ) );
		}
		else {
			printf( "Outgoing #: %d\n", n - half - 1);
			printf( "Introverted #: %d\n", half + 1);
			printf( "Diff = %d\n", aabs( sum[n] - sum[half + 1] - sum[half + 1] ) );
		}
	}
	else {
		ci32 half = n / 2;
		printf( "Outgoing #: %d\n", n - half);
		printf( "Introverted #: %d\n", half );
		printf( "Diff = %d\n", aabs( sum[n] - sum[half] - sum[half] ) );
	}
}
