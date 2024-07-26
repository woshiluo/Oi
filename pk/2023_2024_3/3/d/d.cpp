/*
 * d.cpp 2024-07-09
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

const int N = 3e5 + 1e4;

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		static char ra[N], rb[N], rc[N];
		scanf( "%s%s%s", ra + 1, rb + 1, rc + 1 );
		std::vector<i32> cnt(5);
		for( int i = 1; i <= n; i ++ ) {
			if( ra[i] != rb[i] && rb[i] != rc[i] && ra[i] != rc[i] ) {
				cnt[0] ++;
				continue;
			}
			if( ra[i] == rb[i] && rb[i] == rc[i] ) {
				cnt[1] ++;
				continue;
			}
			if( ra[i] == rb[i] ) {
				cnt[2] ++;
				continue;
			}
			if( ra[i] == rc[i] ) {
				cnt[3] ++;
				continue;
			}
			if( rc[i] == rb[i] ) {
				cnt[4] ++;
				continue;
			}
		}

		ci32 min = std::min( { cnt[2], cnt[3], cnt[4] } );
		i32 base = cnt[1] + min * 2;
		
		cnt[2] -= min;
		cnt[3] -= min;
		cnt[4] -= min;

		for( int p = 2; p <= 4; p ++ ) {
			ci32 k = Min( cnt[0], cnt[p] );
			cnt[p] -= k;
			cnt[0] -= k;
			base += k;

			base += ( cnt[p] >> 1 );
			cnt[p] &= 1;
		}

		ci32 tot = cnt[2] + cnt[3] + cnt[4];

		if( tot == 0 ) {
			printf( "%d\n", base + cnt[0] / 3 );
		}
		else {
			printf( "%d\n", base + ( tot == 2 ) );
		}
	}
}
