/*
 * a.cpp 2024-07-31
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
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		static char buf[16], res[16];
		scanf( "%s", buf );

		i32 max = 0;
		ci32 len = strlen(buf);
		for( char x = 'a'; x <= 'z'; x ++ ) {
			static char nxt[16];
			for( int i = 0; i <= len; i ++ ) {
				for( int j = 0; j <= len; j ++ ) {
					if( j < i )
						nxt[j] = buf[j];
					if( j > i )
						nxt[j] = buf[ j - 1 ];
					if( i == j ) 
						nxt[j] = x;
				}
				nxt[ len + 1 ] = 0;
				i32 cur = 0;
				char la = 0;
				for( int j = 0; j <= len; j ++ ) {
					if( nxt[j] == la ) 
						cur ++;
					else 
						cur += 2;
					la = nxt[j];
				}

				if( cur > max ) {
					max = cur;
					strcpy( res, nxt );
				}
			}
		}
		printf( "%s\n", res );
	}
}
