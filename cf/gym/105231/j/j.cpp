/*
 * j.cpp 2024-09-13
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

enum Type {
	type_s,
	type_p,
	type_m,
	type_z,
};

Type get_type( const char x ) {
	switch(x) {
		case 's': 
			return type_s;
		case 'p': 
			return type_p;
		case 'm': 
			return type_m;
		case 'z': 
			return type_z;
		default:
			return type_s;
	}
}

int main() {
#ifdef woshiluo
	freopen( "j.in", "r", stdin );
	freopen( "j.out", "w", stdout );
#endif

	i32 T = read<i32>();

	while( T -- ) {
		static char buf[64];
		scanf( "%s", buf );

		std::vector<std::pair<i32, Type>> list;
		for( int i = 0; i < 28; i += 2 ) {
			list.push_back( std::make_pair( buf[i] - '0', get_type( buf[ i + 1 ] ) ) );
		}
		std::sort( list.begin(), list.end() );

		// check 13 o
		{
			auto l2 = list;
			l2.erase( std::unique( l2.begin(), l2.end() ), l2.end() );
			bool flag = true;
			if( l2.size() == list.size() - 1 ) {
				for( auto &[ x, type ]: l2 ) {
					if( type != type_z ) 
						if( x != 1 && x != 9 ) 
							flag = false;
				}
			}
			else
				flag = false;

			if( flag ) {
				printf( "Thirteen Orphans\n" );
				continue;
			}
		}

		// check 7-pairs
		{
			auto l2 = list;
			l2.erase( std::unique( l2.begin(), l2.end() ), l2.end() );
			bool flag = true;
			if( l2.size() == 7 ) {
				for( auto &p1: l2 ) {
					i32 cnt = 0;
					for( auto &p2: list ) 
						cnt += ( p1 == p2 );
					if( cnt != 2 ) 
						flag = false;
				}
			}
			else
				flag = false;
			if( flag ) {
				printf( "7 Pairs\n" );
				continue;
			}

		}

		printf( "Otherwise\n" );
	}
}
