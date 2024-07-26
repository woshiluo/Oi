/*
 * d.cpp 2024-07-24
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

const int K = 18;
const int N = 1 << 19;

int full_pow( ci32 cur ) { return 1 << cur; }
int chk_pos( ci32 cur, ci32 pos ) { return ( cur >> pos ) & 1; } 

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = read<i32>();

	while( T -- ) {
		ci32 n = read<i32>();
		ci32 c = read<i32>();
		ci32 k = read<i32>();

		std::vector<i32> f( 1 << c ), la(c);

		static char str[N];
		scanf( "%s", str + 1);

		for( int i = 1; i <= n; i ++ ) {
			la[ str[i] - 'A' ] = i;

			i32 mask = 0;
			for( int j = 0; j < c; j ++ ) {
				if( i - la[j] >= k ) {
					mask |= full_pow(j);
				}
			}

			f[mask] = 1;
		}

		for (int i = 0; i < full_pow(c); ++i) {  
			if( !f[i] ) 
				continue;
			for (int j = i; j; j = (j - 1) & i) {
				f[j] = 1;
			}
			f[0] = 1;
		}

		i32 res = c;
		for( int i = 0; i < full_pow(c);i ++ ) {
			if( !chk_pos( i, str[n] - 'A' ) ) 
				continue;
			if( !f[i] ) 
				chk_Min( res, __builtin_popcount(i) );
		}
		printf( "%d\n", res );
	}
	
}
