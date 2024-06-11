/*
 * c.cpp 2024-05-26
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

i64 gcd( i64 a, i64 b ) { return b? gcd( b, a % b ): a; }
i64 lcm( i64 a, i64 b ) { return a / gcd( a, b ) * b; }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	i32 T = read<i32>();
	while( T -- ) {
		i32 n = read<i32>();
		std::map<i32, i32> mp;
		std::vector<std::pair<i32, i32>> list;
		for( int i = 0; i < n; i ++ ) {
			int x = read<i32>();
			mp[x] ++;
		}
		ci32 max = mp.rbegin() -> first;
		bool flag = false;
		for( auto [x, y]: mp ) {
			list.push_back( std::make_pair( x, y ) );
			if( max % x != 0 ) {
				flag = true;
				break;
			}
		}
		if( flag ) {
			printf( "%d\n", n );
			continue;
		}
		i32 res = 0;
		// TODO: is lcm possible be one?
		//
		auto check = [&]( int target ) {
			int p = 1;
			int cnt = 0;
			for( auto &[x, y]: list ) {
				if( target % x == 0 ) {
					p = lcm( x, p );
					cnt += y;
				}
			}
			if( p == target ) {
				chk_Max( res, cnt );
			}
		};
		for( int i = 1; 1LL * i * i <= max; i ++ ) {
			if( max % i != 0 )
				continue;
			if( mp.count(i) == 0 )
				check(i);
			if( mp.count( max / i ) == 0 ) {
				check( max / i );
			}
		}
		printf( "%d\n", res );
	}
}

