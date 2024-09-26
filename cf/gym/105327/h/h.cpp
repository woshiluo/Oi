/*
 * h.cpp 2024-09-25
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

const int ML = 512;
const int NL = 32;

char sn[NL], sm[ML];

bool chk_pos( ci32 cur, ci32 pos ) { return ( cur >> pos ) & 1; }
i32 pow_2( ci32 cur ) { return 1 << cur; }

int main() {
#ifdef woshiluo
	freopen( "h.in", "r", stdin );
	freopen( "h.out", "w", stdout );
#endif

	scanf( "%s", sm + 1 );
	scanf( "%s", sn + 1 );

	ci32 ln = strlen( sn + 1 );
	ci32 lm = strlen( sm + 1 );

	std::vector<std::pair<i32, i32>> lost;
	// 0 n
	// 1 m
	for( int i = 1; i <= ln; i ++ ) {
		if( sn[i] == '*' ) 
			lost.emplace_back( 0, i );
	}
	for( int i = 1; i <= lm; i ++ ) {
		if( sm[i] == '*' ) 
			lost.emplace_back( 1, i );
	}

	ci32 lost_cnt = lost.size();
	for( i32 mask = 0; mask < pow_2( lost_cnt ); mask ++ ) {
		for( int i = 0; i < lost_cnt; i ++ ) {
			const auto &[k, p] = lost[i];
			if( chk_pos( mask, i ) ) {
				if( k ) 
					sm[p] = '1';
				else 
					sn[p] = '1';
			}
			else {
				if( k ) 
					sm[p] = '0';
				else 
					sn[p] = '0';
			}
		}
		i64 n = 0;

		for( int i = 1; i <= ln; i ++ ) {
			n <<= 1;
			n |= ( sn[i] - '0' );
		}

		i64 m = 0;
		for( int i = 1; i <= lm; i ++ ) {
			m <<= 1;
			m |= ( sm[i] - '0' );
			m %= n;
		}

		if( m == 0 ) {
			printf( "%s\n", sm + 1 );
			return 0;
		}
	}
}
