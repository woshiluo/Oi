/*
 * j.cpp 2024-08-08
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
	freopen( "j.in", "r", stdin );
	freopen( "j.out", "w", stdout );
#endif
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		if( m == n - 2 ) {
			printf( "-1\n" );
			continue;
		}
		std::vector<i32> list;
		ci32 less = n - m;
		{
			ci32 p = less / 3;
			for( int i = 1; i <= p; i ++ ) {
				list.push_back( 2 * p - i + 1 );
				list.push_back( p - i + 1 );
				list.push_back( 3 * p - i + 1 );
			}
		}
		if( less % 3 == 0 ) {
			std::swap( list[ less - 3 ], list[ less - 2 ] );
		}
		if( less % 3 == 1 ) {
			list.insert( list.begin(), less );
			std::reverse( list.begin(), list.end() );
		}
		if( less % 3 == 2 ) {
			list.push_back( less - 1 );
			list.insert( list.begin(), less );
			std::reverse( list.begin(), list.end() );
		}
		for( int i = 1; i <= m; i ++ ) {
			list.push_back( less + i );
		}
		for( auto &x: list )
			printf( "%d ", x );
//		int cnt = 0;
//		for( int i = 0; i < n; i ++ ) {
//			std::vector<i32> p;
//			for( int j = 0; j < 3; j ++ ) {
//				if( i + j >= n ) 
//					break;
//				p.push_back( list[ i + j ] );
//			}
//			if( p.size() != 3 )
//				continue;
//			if( p[0] + p[1] > p[2] && p[1] + p[2] > p[0] && p[0] + p[2] > p[1] ) 
//				cnt ++;
//		}
//		if( cnt != m ) 
//			std::exit(-1);
		printf( "\n" );
	}

	
}
