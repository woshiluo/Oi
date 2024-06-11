/*
 * c.cpp 2024-06-06
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

i32 gcd( i32 a, i32 b ) { return b? gcd( b, a % b ): a; }
i32 lcm( i32 a, i32 b ) { return 1LL * a / gcd(a,b) * b; }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> a(n);
		i32 cur_lcm = 1;
		for( auto &x: a ) {
			x = read<i32>();
			cur_lcm = lcm( x, cur_lcm );
		}
		auto check = [&]( const i64 target, const bool output = false ) {
			std::vector<i64> list;
			for( auto &x: a ) {
				list.push_back( target / x + ( target % x != 0 ) );
			}
			i64 sum = 0;
			for( auto &x: list )
				sum += x;
			if( output ) {
				for( auto &x: list ) 
					printf( "%lld ", x );
				printf( "\n" );
			}
			return sum < target;
		};
		if( check( cur_lcm * 2 - 1 ) ) {
			check( cur_lcm * 2 - 1, true );
		}
		else
			printf( "-1\n" );
	}
}
