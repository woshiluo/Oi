/*
 * l.cpp 2024-09-21
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cmath>
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
	freopen( "l.in", "r", stdin );
	freopen( "l.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> a(n + 1);
		for( int i = 1; i <= n; i ++ ) 
			a[i] = read<i32>();
		std::vector<i32> lens;
		std::vector<i64> sum( n + 1 );
		ci32 sqrt = 400;
		for( int i = 1; i <= sqrt && i <= n; i ++ )
			lens.push_back(i);
		for( int i = Max( 1, ( n >> 1 ) - sqrt ); i <= ( n >> 1 ) + sqrt && i <= n; i ++ )
			lens.push_back(i);
		for( int i = 1; i <= n; i ++ ) 
			sum[i] = sum[ i - 1 ] + a[i];

		std::sort( lens.begin(), lens.end() );
		lens.erase( std::unique( lens.begin(), lens.end() ), lens.end() );

		i32 res = 0;
		for( auto &len: lens ) {
			ci64 target = 1LL * len * len;
			for( int i = 1; i <= n && i + len - 1 <= n; i ++ ) {
				ci64 cur = sum[ i + len - 1 ] - sum[ i - 1 ];
				if( cur == target ) 
					res ++;
			}
		}

		printf( "%d\n", res );
	}
	return 0;
}
