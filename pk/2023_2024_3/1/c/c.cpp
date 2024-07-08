/*
 * c.cpp 2024-07-07
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

const int N = 610;

i64 f[N][N];
i64 sum[N][N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	std::vector<i32> a(n);
	for( auto &x: a )
		x = read<i32>();
	std::vector<i32> b = a;
	for( auto &x: a )
		b.push_back(x);
	
	ci32 m = n * 2;
	for( int i = 0; i < m; i ++ ) {
		for( int j = i; j < m; j ++ ) {
			if( j != 0 )
				sum[i][j] = sum[i][ j - 1 ] + std::abs( b[i] - b[j] );
			else
				sum[i][j] = std::abs( b[i] - b[j] );
		}
	}
	for( int i = 0; i < m - 1; i ++ ) {
		f[i][ i + 1 ] = std::abs( b[i] - b[ i + 1 ] );
	}

	for( int len = 3; len <= n; len ++ ) {
		for( int l = 0; len + l - 1 < m; l ++ ) {
			ci32 r = len + l - 1;
			f[l][r] = sum[l][r];
			for( int mid = l + 1; mid <= r; mid ++ ) {
				// chk_Max( f[l][r], sum[l][ mid - 1 ] + f[mid][r] + std::abs( b[l] - b[mid] ) );
				chk_Max( f[l][r], f[l][mid - 1] + f[mid][r] + std::abs( b[l] - b[mid] ) );
			}
		}
	}

	i64 res = f[0][ n - 1 ];
	for( int i = 0; i + n - 1 < m; i ++ ) {
		chk_Max( res, f[i][ i + n - 1 ] );
	}

	printf( "%lld\n", res );
}
