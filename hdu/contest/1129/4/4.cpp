/*
 * 4.cpp 2024-08-05
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
	freopen( "4.in", "r", stdin );
	freopen( "4.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		std::vector< std::pair<i32, i32> > a, b;
		for( int i = 1; i <= n; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			a.emplace_back( u, v );
		}
		for( int i = 1; i <= m; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			b.emplace_back( u, v );
		}

		i32 la = 0;
		i32 p1 = 0;
		bool flag = true;
		for( int i = 0; i < m; i ++ ) {
			while( p1 < n && a[p1].first < b[i].second ) {
				if( a[p1].second > la ) 
					flag = false;
				if( a[p1].second > b[i].first ) 
					flag = false;
				p1 ++;
			}
			la = b[i].second + ( b[i].second - b[i].first ) * 2;
		}
		while( p1 < n ) {
			if( a[p1].second > la ) 
				flag = false;
			p1 ++;
		}

		if( flag )
			printf( "Yes\n" );
		else 
			printf( "No\n" );
	}
}
