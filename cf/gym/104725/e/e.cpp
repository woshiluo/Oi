/*
 * e.cpp 2023-10-25
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

const i32 N = 30;
const i32 K = 15;
const int POW_3_K = 531441;

i32 pow_3[K];

constexpr i32 set_pos( ci32 cur, ci32 pos, ci32 val ) { return ( ( cur / pow_3[ pos + 1 ] ) + val ) * 3; }
constexpr i32 chk_pos( ci32 cur, ci32 pos ) { return ( cur / pow_3[pos] ) % 3; }

double f[2][N][POW_3_K];

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();
	ci32 k = read<i32>();

	pow_3[0] = 1;
	for( int i = 1; i < k; i ++ ) {
		pow_3[i] = pow_3[ i - 1 ] * 3;
	}

	int cur = 0, nxt = 1;
	for( i32 sta = 0; sta < pow_3[k]; sta ++ ) {
		int cnt_get = 0, cnt_des = 0;
		for( i32 i = 0; i < k; i ++ ) {
			if( chk_pos( sta, i ) == 1 ) 
				cnt_des ++;
			if( chk_pos( sta, i ) == 2 ) 
				cnt_get ++;
		}

		if( cnt_des + cnt_get != k ) 
			continue;

		for( int i = 0; i < n; i ++ ) {
			f[cur][i][cnt_get] = cnt_get;
		}
	}

	for( int p = 31; p >= 0; p --, cur ^= 1, nxt ^= 1 ) {
		for( int i = 1; i <= n; i ++ ) {
		}
	}
}
