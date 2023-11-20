/*
 * a.cpp 2023-10-25
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
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

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		std::vector<i32> list[9], pos[3];
		list[1].push_back(1);
		list[2].push_back(2);
		list[3].push_back(3);
		for( int _ = 1; _ <= 12; _ ++ ) {
			ci32 p = read<i32>();
			ci32 d = read<i32>();
			for( int i = 0; i < 9; i ++ ) {
				std::vector<i32> curs;
				bool flag = false;
				for( auto &x: list[i] ) {
					if( x == p ) {
						flag = true;
						break;
					}
				}
				if( !flag ) 
					continue;

				while( list[i].back() != p ) {
					curs.push_back( list[i].back() );
					list[i].pop_back();
				}
				curs.push_back( list[i].back() );
				list[i].pop_back();

				ci32 nxt = i + d;
				while( !curs.empty() ) {
					list[nxt].push_back( curs.back() );
					curs.pop_back();
				}

				break;
			}
		}

		if( list[8].size() == 3 ) 
			printf( "Y\n" );
		else
			printf( "N\n" );
	}
}
