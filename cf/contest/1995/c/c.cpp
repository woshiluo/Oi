/*
 * c.cpp 2024-07-23
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

using i64 = long long;
using u64 = uint64_t;
using ci64 = const i64;
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

const int K = 22;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 T = read<i32>();

	while( T -- ) {
		ci32 n = read<i32>();
		i32 la = 0, la_p = 0;
		i64 res = 0;
		bool flag = false;
		for( int i = 1; i <= n; i ++ ) {
			ci32 cur = read<i32>();
			if( flag ) 
				continue;
			if( cur == 1 ) {
				if( la <= 1 ) {
					la = 1;
					continue;
				}
				flag = true;
				continue;
			}
			if( cur < la ) {
				int cp = 1;
				for( int k = 1; k < K; k ++ ) {
					if( pow( ( (i64)cur ), 1 << k ) >= la ) {
						cp = k;
						break;
					}
				}
				la = cur;
				la_p += cp;
				res += la_p;
				continue;
			}
			if( cur > la ) {
				int cp = 1;
				for( int k = 1; k < K; k ++ ) {
					if( pow( ( (i64)la ), 1 << k ) > cur ) {
						cp = k;
						break;
					}
				}
				la = cur;
				la_p -= cp - 1;
				chk_Max( la_p, 0 );
				res += la_p;
				continue;
			}
			if( cur == la ) {
				res += la_p;
			}
		}
		if( flag ) 
			printf( "-1\n" );
		else
			printf( "%lld\n", res );
	}
}
