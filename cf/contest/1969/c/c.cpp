/*
 * c.cpp 2024-04-29
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

const int N = 3e5 + 1e4;
const int K = 16;
const long long LLF = 0x3f3f3f3f3f3f3f3full;

int a[N];
long long f[N][K];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 k = read<i32>();
		for( int i = 0; i <= n; i ++ ) {
			if( i != 0 )
				a[i] = read<i32>();
			for( int j = 0; j < K; j ++ ) {
				f[i][j] = LLF;
			}
		}

		f[0][0] = 0;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 0; j <= k; j ++ ) {
				i32 min = a[i];
				for( int p = 1; p <= k + 1 && j - p + 1 >= 0 && i - p >= 0; p ++ ) {
					chk_Min( min, a[ i - p + 1 ] );
					chk_Min( f[i][j], f[ i - p ][ j - p + 1 ] + 1LL * min * p );
				}
			}
		}

		long long res = LLF;
		for( int j = 0; j <= k; j ++ ) {
			chk_Min( res, f[n][j] );
		}
		printf( "%lld\n", res );
	}
}
