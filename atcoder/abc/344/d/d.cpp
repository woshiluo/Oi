/*
 * d.cpp 2024-03-11
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
const int INF = 0x3f3f3f3f;

char str[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%s", str + 1);
	ci32 len = strlen(str + 1);
	ci32 n = read<i32>();
	std::vector<std::vector<i32>> f( N, std::vector<i32>( N, INF ) );
	f[0][0] = 0;
	for( int i = 1; i <= n; i ++ ) {
		f[i][0] = 0;
		ci32 k = read<i32>();
		for( int j = 0; j < k; j ++ ) {
			static char op[16];
			scanf( "%s", op );
			i32 oplen = strlen(op);
			for( int p = 1; p <= len; p ++ ) {
				chk_Min( f[i][p], f[ i - 1 ][p] );
				if( p + oplen > N ) 
					break;
				ci32 tmp = str[ p + oplen ];
				str[ p + oplen ] = 0;
				if( strcmp( str + p, op ) == 0 ) {
					chk_Min( f[i][ p + oplen - 1 ], f[ i - 1 ][ p - 1 ] + 1 );
				}
				str[ p + oplen ] = tmp;
			}
		}
	}

	if( f[n][len] == INF )
		printf( "-1\n" );
	else
		printf( "%d\n", f[n][len] );
}
