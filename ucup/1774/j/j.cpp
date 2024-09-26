/*
 * j.cpp 2024-09-21
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

const int N = 64;

int f[N][3];
// 0 0
// 1 1
// 2 0

int main() {
#ifdef woshiluo
	freopen( "j.in", "r", stdin );
	freopen( "j.out", "w", stdout );
#endif

	static char buf[N];

	scanf( "%s", buf + 1 );

	ci32 len = strlen( buf + 1 );


	memset( f, 0x3f, sizeof(f) );
	f[0][0] = 0;
	f[0][1] = 0;
	for( int i = 1; i <= len; i ++ ) {
		f[i][0] = f[ i - 1 ][0] + ( buf[i] != '0' );
		f[i][1] = Min( f[ i - 1 ][0], f[ i - 1 ][1] ) + ( buf[i] != '1' );
		f[i][2] = Min( f[ i - 1 ][1], f[ i - 1 ][2] ) + ( buf[i] != '0' );
	}

	printf( "%d\n", Min( f[len][0], Min( f[len][1], f[len][2] ) ) );

	return 0;
}
