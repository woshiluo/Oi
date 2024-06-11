/*
 * e.cpp 2024-03-06
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

const i32 K = 30;

int full_pow( ci32 cur ) { return 1 << cur; }
bool chk_pos( ci32 cur, ci32 k ) { return ( cur >> k ) & 1; }

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> lx, ly, lb;
		for( int i = 1; i <= n; i ++ ) {
			ci32 x = read<i32>();
			ci32 y = read<i32>();
			i32 base = 0;
			for( int k = K - 1; k >= 0; k -- ) {
				if( chk_pos( x, k ) == chk_pos( y, k ) ) {
					if( chk_pos( x, k ) )
						base |= full_pow(k);
				}
				else 
					break;
			}
			lx.push_back( x - base );
			ly.push_back( y - base );
			lb.push_back(base);
		}
		std::vector<std::vector<i32>> sum( n, std::vector<i32>(K) );
		std::vector<std::vector<i32>> base( n, std::vector<i32>(K) );
		for( int i = 0; i < n; i ++ ) {
			for( int k = 0; k < K; k ++ ) {
				sum[i][k] += chk_pos( ly[i], k );
				base[i][k] += chk_pos( lb[i], k );
				if( i != 0 ) {
					sum[i][k] += sum[ i - 1 ][k];
					base[i][k] += base[ i - 1 ][k];
				}
			}
		}
		i32 q = read<i32>();
		auto query = [&] ( std::vector<std::vector<i32>> &s, ci32 l, ci32 r, ci32 k ) {
			if( l == 0 ) 
				return s[r][k];
			else
				return s[r][k] - s[ l - 1 ][k];
		};
		while( q -- ) {
			ci32 l = read<i32>() - 1;
			ci32 r = read<i32>() - 1;
			i32 res = 0;
			for( int i = K - 1; i >= 0; i -- ) {
				ci32 cnt = ( query( base, l, r, i ) != 0 ) + ( query( sum, l, r, i ) );
				if( cnt == 0 )
					continue;
				if( cnt == 1 ) {
					res |= full_pow(i);
				}
				else {
					res |= full_pow( i + 1 ) - 1;
					break;
				}
			}
			printf( "%d ", res );
		}
		printf( "\n" );
	}
}
