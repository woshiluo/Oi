/*
 * d.cpp 2024-08-06
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

#include <set>
#include <map>
#include <random>
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

using i128 = __int128;
using u128 = unsigned __int128;
using ci128 = const i128;
using cu128 = const u128;

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

std::random_device seed;
std::mt19937_64 rnd(seed());

u64 add( cu64 p, cu64 q, ci32 k ) {
	u64 res = 0;
	for( i128 offset = 1; offset * k < UINT64_MAX; offset *= k ) {
		cu64 p1 = ( p / offset ) % k;
		cu64 p2 = ( q / offset ) % k;
		res += ( ( p1 + p2 ) % k ) * offset;
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		std::map<i32, u64> hashed;
		std::map<i32, i32> count;
		std::multiset<u64> valid;
		ci32 n = read<i32>();
		ci32 k = read<i32>();
		std::vector<i32> a( n + 1 );
		std::vector<u64> sum( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<i32>();
			if( hashed.count( a[i] ) == 0 ) {
				hashed[ a[i] ] = rnd();
			}
		}
		i64 res = 0;
		int p1 = 1;
		valid.insert(0);
		for( int i = 1; i <= n; i ++ ) {
			count[ a[i] ] ++;
			while( count[ a[i] ] > k ) {
				count[ a[p1] ] --;
				if( k != 1 )
					valid.erase( valid.find( sum[p1 - 1] ) );
				p1 ++;
			}
			if( k == 1 ) 
				res += i - p1 + 1;
			else {
				sum[i] = add( sum[ i - 1 ], hashed[ a[i] ], k );
				res += valid.count( sum[i] );
				valid.insert( sum[i] );
			}
		}

		printf( "%" PRId64 "\n", res );
	}
}
