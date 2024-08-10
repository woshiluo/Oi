/*
 * 10.cpp 2024-08-09
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

int main() {
#ifdef woshiluo
	freopen( "10.in", "r", stdin );
	freopen( "10.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 x = read<i32>();
		ci32 k = read<i32>();
		std::vector<i32> a(n);
		for( auto &x: a ) 
			x = read<i32>();

		auto check = [&]( ci32 mid ) {
			std::vector<i32> b;
			for( int i = 0; i < mid; i ++ ) {
				b.push_back( a[i] );
			}
			std::sort( b.begin(), b.end() );
			i64 res = 0;
			for( int i = 0; i < Max( mid - k, 0 ); i ++ ) {
				res += b[i];
			}
			return res < x;
		};

		i32 left = 1, rig = n, res = 0;
		while( left <= rig ) {
			ci32 mid = ( left + rig ) >> 1;
			if( check(mid) ) {
				res = mid;
				left = mid + 1;
			}
			else 
				rig = mid - 1;
		}
		printf( "%d\n", res );
	}
	
}
