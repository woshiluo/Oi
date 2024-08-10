/*
 * b.cpp 2024-08-04
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

#include <queue>
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
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i64> l1, l2;
		for( int i = 1; i <= n; i ++ ) {
			ci32 x = read<i32>();
			if( x & 1 ) 
				l1.push_back(x);
			else
				l2.push_back(x);
		}

		if( l1.size() == 0 || l2.size() == 0 ) {
			printf( "0\n" );
			continue;
		}
		else {
			std::sort( l1.begin(), l1.end() );
			std::sort( l2.begin(), l2.end() );
			std::reverse( l2.begin(), l2.end() );

			int res = 0;
			while( !l2.empty() ) {
				res ++;
				if( l2.back() > l1.back() ) {
					l1.push_back( l1.back() + l2.front() );
				}
				else {
					l1.push_back( l1.back() + l2.back() );
					l2.pop_back();
				}
			}
			printf( "%d\n", res );
		}
	}
}
