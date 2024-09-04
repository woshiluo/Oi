/*
 * f.cpp 2024-09-04
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


i64 gcd( i64 a, i64 b ) { return b? gcd( b, a % b ): a; }
i32 pow_2( ci32 cur ) { return 1LL << cur; }
bool chk_pos( ci32 mask, ci32 pos ) { return ( mask >> pos ) & 1; }

const int K = 19;

i64 pow_10[K];

bool check( std::vector<i32> l1, std::vector<i32> l2 ) {
	ci32 s1 = l1.size(), s2 = l2.size();
	i32 p1 = 0, p2 = 0;
	while( p1 < s1 && p2 < s2 ) {
		if( l1[p1] == l2[p2] ) 
			p1 ++, p2 ++;
		else 
			p1 ++;
	}
	return p2 == s2;
}

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	pow_10[0] = 1;
	for( int k = 1; k < K; k ++ ) 
		pow_10[k] = pow_10[ k - 1 ] * 10;

	auto parse_dec = [] ( __int128 cur, std::vector<i32> &l ) {
		while(cur) {
			l.push_back( cur % 10 );
			cur /= 10;
		}
		std::reverse( l.begin(), l.end() );
	};

	ci64 a = read<i64>();
	ci64 b = read<i64>();
	ci64 tc = read<i64>();
	ci64 td = read<i64>();

	ci64 p = gcd( tc, td );
	ci64 c = tc / p;
	ci64 d = td / p;

	std::vector<i32> la, lb;
	parse_dec( a, la );
	parse_dec( b, lb );

	ci32 log_a = la.size();
	for( int mask = 1; mask < pow_2(log_a); mask ++ ) {
		std::vector<i32> list;
		for( int i = 0; i < K; i ++ ) {
			if( chk_pos( mask, i ) ) {
				list.push_back( la[i] );
			}
		}
		__int128 res = 0;
		for( auto &x: list ) {
			res = res * 10 + x;
		}
		if( res == 0 ) 
			continue;
		if( res % c != 0 ) 
			continue;
		__int128 nb = res / c * d;
		std::vector<i32> lnb;
		parse_dec( nb, lnb );
		if( check( lb, lnb ) ) {
			printf( "possible\n" );
			for( auto &x: list ) 
				printf( "%d", x );
			printf( " " );
			for( auto &x: lnb ) 
				printf( "%d", x );
			return 0;
		}
	}
	printf( "impossible\n" );
}
