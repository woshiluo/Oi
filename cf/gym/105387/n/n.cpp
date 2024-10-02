/*
 * n.cpp 2024-10-02
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
#include <cinttypes>

#include <vector>
#include <string>
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

const int N = 1100;

int main() {
#ifdef woshiluo
	freopen( "n.in", "r", stdin );
	freopen( "n.out", "w", stdout );
#endif


	ci32 n = read<i32>();
	i64 l = 0, r = 1e18;
	for( int i = 1; i <= n; i ++ ) {
		static char buf[N];
		scanf( "%s", buf );
		if( buf[0] == '?' ) 
			continue;

		ci64 res = std::stoi( buf, NULL, 10 );
		ci64 lp1 = ( res - 1 ) * i;
		ci64 lp2 = res * i;
		ci64 cl = ( ( lp1 + lp2 ) ) / 2LL + ( ( lp1 + lp2 ) & 1LL );
		ci64 rp1 = res * i;
		ci64 rp2 = ( res + 1 ) * i;
		ci64 cr = ( ( rp1 + rp2 ) ) / 2LL + ( ( rp1 + rp2 ) & 1LL );
		chk_Max( l, cl );
		chk_Min( r, cr );
	}
	printf( "%" PRId64 "\n", l );

	return 0;
}
