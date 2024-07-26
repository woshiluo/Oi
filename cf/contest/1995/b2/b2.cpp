/*
 * b1.cpp 2024-07-23
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

using i64 = long long;
using u64 = unsigned long long;
using ci64 = const i64;
using cu64 = const u64;

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

int main() {
#ifdef woshiluo
	freopen( "b2.in", "r", stdin );
	freopen( "b2.out", "w", stdout );
#endif

	i32 T = read<i32>();

	while( T -- ) {
		ci64 n = read<i64>();
		ci64 m = read<i64>();

		std::vector<i64> l1(n), l2(n);
		for( auto &x: l1 ) 
			x = read<i64>();
		for( auto &x: l2 ) 
			x = read<i64>();

		std::map<i64, i64> mp;
		for( int i = 0; i < n; i ++ ) 
			mp[ l1[i] ] += l2[i];
		
		i64 res = 0;
		for( auto &[ x, y ]: mp ) {
			i64 cur_c = mp[x];
			i64 nxt_c = ( mp.count( x + 1 )? mp[ x + 1 ]: 0 );

			ci64 max = cur_c * x + nxt_c * ( x + 1 );
			if( max <= m ) {
				chk_Max( res, max );
			}
			else {
				i64 mc = Min( m / x, cur_c );
				i64 base = mc * x;
				i64 less = m - base;
				i64 mn = Min( less / ( x + 1 ), nxt_c );
				base += mn * ( x + 1 );
				less -= mn * ( x + 1 );

				less -= Min( Min( mc, nxt_c - mn ), less );

				chk_Max( res, m - less );
			}
		}
		printf( "%lld\n", res );
	}
	
}
