/*
 * e.cpp 2024-09-13
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

#include <map>
#include <utility>
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

const int K = 20;

int pow_3[K];

int chk_pos_3( ci32 cur, ci32 pos ) { return ( cur / pow_3[pos] ) % 3; }

void print( ci32 total, ci32 p1, ci32 p2, ci32 mask1, ci32 mask2 ) {
	std::vector<i32> l1, l2;
	for( int i = 0; i < p1; i ++ ) {
		ci32 bit = chk_pos_3( mask1, i );
		if( bit == 0 ) 
			continue;
		if( bit == 1 ) 
			l1.push_back(i);
		else
			l2.push_back(i);
	}
	for( int i = 0; i < p2; i ++ ) {
		ci32 bit = chk_pos_3( mask2, i );
		if( bit == 0 ) 
			continue;
		if( bit == 1 ) 
			l1.push_back(i + p1);
		else
			l2.push_back(i + p1);
	}
	printf( "%lu ", l1.size() );
	for( auto &x: l1 ) {
		printf( "%d ", x + 1 );
	}
	printf( "\n" );
	printf( "%lu ", l2.size() );
	for( auto &x: l2 ) {
		printf( "%d ", x + 1 );
	}
	printf( "\n" );
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	pow_3[0] = 1;
	for( int i = 1; i < K; i ++ ) {
		pow_3[i] = pow_3[ i - 1 ] * 3;
	}

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> a(n);
		for( auto &x: a ) 
			x = read<i32>();
		std::vector<i32> b = a;
		std::sort( b.begin(), b.end() );
		b.erase( std::unique( b.begin(), b.end() ), b.end() );
		if( (i32)b.size() != n ) {
			std::map<i32, i32> la;
			for( int i = 0; i < n; i ++ ) {
				if( la.count( a[i] ) ) {
					printf( "1 %d\n1 %d\n", la[ a[i] ] + 1, i + 1 );
					break;
				}
				la[ a[i] ] = i;
			}
			continue;
		}
		if( n <= 15 ) {
			bool flag = false;
			for( int mask = 0; mask < pow_3[n]; mask ++ ) {
				i64 s1 = 0, s2 = 0;
				for( int i = 0; i < n; i ++ ) {
					ci32 bit =  chk_pos_3( mask, i );
					if( bit == 0 ) 
						continue;
					if( bit == 1 ) 
						s1 += a[i];
					else
						s2 += a[i];
				}
				if( s1 == 0 || s2 == 0 ) {
					continue;
				}
				if( s1 == s2 ) {
					flag = true;
					print( n, n, 0, mask, 0 );
					break;
				}
			}
			if( !flag ) 
				printf( "-1\n" );
		}
		else {
			ci32 rn = Min( 25, n );
			ci32 p1 = ( rn >> 1 );
			ci32 p2 = rn - p1;
			std::map<i32, i32> mp, e1, e2;
			bool flag = false;
			for( int mask = 0; mask < pow_3[p1]; mask ++ ) {
				i64 s1 = 0, s2 = 0;
				for( int i = 0; i < p1; i ++ ) {
					ci32 bit =  chk_pos_3( mask, i );
					if( bit == 0 ) 
						continue;
					if( bit == 1 ) 
						s1 += a[i];
					else
						s2 += a[i];
				}
				if( s1 != 0 && s2 != 0 ) 
					mp[ s1 - s2 ] = mask;
				if( s1 == 0 && s2 != 0 ) 
					e1[ s1 - s2 ] = mask;
				if( s1 != 0 && s2 == 0 )
					e2[ s1 - s2 ] = mask;
			}
			for( int mask = 0; mask < pow_3[p2]; mask ++ ) {
				i64 s1 = 0, s2 = 0;
				for( int i = 0; i < p2; i ++ ) {
					ci32 bit =  chk_pos_3( mask, i );
					if( bit == 0 ) 
						continue;
					if( bit == 1 ) 
						s1 += a[i + p1];
					else
						s2 += a[i + p1];
				}
				if( mp.count( s2 - s1 ) ) {
					flag = true;
					print( n, p1, p2, mp[ s2 - s1 ], mask );
					break;
				}
				if( s2 != 0 && e2.count( s2 - s1 ) ) {
					flag = true;
					print( n, p1, p2, e2[ s2 - s1 ], mask );
					break;
				}
				if( s1 != 0 && e1.count( s2 - s1 ) ) {
					flag = true;
					print( n, p1, p2, e1[ s2 - s1 ], mask );
					break;
				}
			}
			if( !flag ) 
				printf( "-1\n" );
		}
	}
}
