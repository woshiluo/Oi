/*
 * c.cpp 2024-07-07
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

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> p[3];
		p[0].resize(n); p[1].resize(n); p[2].resize(n);
		i64 tot = 0;
		for( auto &x: p[0] ) {
			x = read<i32>();
			tot += x;
		}
		for( auto &x: p[1] ) 
			x = read<i32>();
		for( auto &x: p[2] ) 
			x = read<i32>();
		
		ci64 tar = ( tot / 3 ) + ( tot % 3 != 0 );

		std::vector<i32> q = { 0, 1, 2 };
		bool flag = false;
		do {
			int ck = 0;
			i64 sum = 0;
			int l[3][2];
			l[ q[0] ][0] = 0;
			for( int i = 0; i < n; i ++ ) {
				sum += p[ q[ck] ][i];
				if( sum >= tar ) {
					l[ q[ck] ][1] = i;
					if( ck + 1 < 3 ) 
						l[ q[ck + 1] ][0] = i + 1;
					ck ++;
					sum = 0;
				}
				if( ck >= 3 ) {
					flag = true;
					break;
				}
			}

			if( flag ) {
				for( int k = 0; k < 3; k ++ ) {
					printf( "%d %d ", l[k][0] + 1, l[k][1] + 1 );
				}
				printf( "\n" );
				break;
			}
		} while( std::next_permutation(q.begin(), q.end() ) );

		if( !flag ) 
			printf( "-1\n" );
	}
	
}
