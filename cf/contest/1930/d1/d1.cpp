/*
 * d1.cpp 2024-02-18
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

const int N = 1e6 + 1e4;
const int INF = 0x3f3f3f3f;

i32 work( const std::vector<i32> &a, ci32 p1, ci32 p2 ) {
	ci32 len = p2 - p1 + 1;
	// 0 x 1
	// 1 1 0 ( not coverd )
	// 2 x 0 ( coverd );
	std::vector<std::vector<i32>> f( len + 1, { INF, INF, 0 } );
	for( int i = 1; i <= len; i ++ ) {
		ci32 cur = a[ p1 + i - 1 ];
		if( cur == 0 ) {
			f[i][0] = Min( f[ i - 1 ][0], Min( f[ i - 1 ][1], f[ i - 1 ][2] ) ) + 1;
			f[i][1] = INF;
			f[i][2] = Min( f[ i - 1 ][0], f[ i - 1 ][2] );
		}
		else {
			f[i][0] = Min( f[ i - 1 ][0], Min( f[ i - 1 ][1], f[ i - 1 ][2] ) ) + 1;
			f[i][1] = f[ i - 1 ][2];
			f[i][2] = f[ i - 1 ][0];
		}
	}
	return Min( f[len][0], f[len][2] );
}

int main() {
#ifdef woshiluo
	freopen( "d1.in", "r", stdin );
	freopen( "d1.out", "w", stdout );
#endif
//	{
//		std::vector<i32> a = { 1, 1, 1, 1, 1, 1, 1 };
//		printf( "%d\n", work( a, 0, a.size() - 1 ) );
//	}
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> a(n);
		{
			static char str[N];
			scanf( "%s", str );
			for( int i = 0; i < n; i ++ ) {
				a[i] = ( str[i] - '0' );
			}
		}
		long long res = 0;
		for( int i = 0; i < n; i ++ ) {
			for( int j = i; j < n; j ++ ) {
				res += work( a, i, j );
			}
		}
		printf( "%lld\n", res );
	}
}
