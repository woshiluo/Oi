/*
 * e.cpp 2024-09-06
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
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		i32 la = -1;
		std::vector<i32> list;
		bool flag = false;
		for( int i = 1; i <= n; i ++ ) {
			i32 p;
			scanf( "%1d", &p );
			if( p == la ) 
				flag = true;
			if( p != la ) {
				if( la != -1 ) 
					list.push_back(flag);
				flag = false;
				la = p;
			}
		}
		list.push_back(flag);
		if( *std::max_element( list.begin(), list.end() ) < 1 ) {
			printf( "0\n" );
			continue;
		}
		ci32 size = list.size();
		i32 max = 0, min = n;
		i32 d = 0, pre = 0;
		for( int i = 0; i < size; i ++ ) {
			if( list[i] == 0 ) 
				continue;
			chk_Max( max, Max( i + 1, size - i ) );
			chk_Max( d, i - pre + 1 );
			pre = i;
		}
		chk_Max( d, size - pre );
		ci32 tar = ( ( size + 1 ) >> 1 ) + ( ( size + 1 ) & 1 );
		if( d >= tar ) 
			min = d;
		else 
			min = tar;
		printf( "%d\n", max - min );
//		printf( "%d %d\n", max, min );
	}
}
