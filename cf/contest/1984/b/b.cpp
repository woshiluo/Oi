/*
 * b.cpp 2024-06-11
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
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci64 x = read<i64>();
		int cnt = 0;
		{
			i64 cur = x;
			while( cur ) {
				cur /= 10;
				cnt ++;
			}
		}
		bool valid = false;
		for( int p = cnt - 1; p < cnt; p ++ ) {
			// l + r 
			// len(r) = p
			
			bool flag = false;
			i64 cur = x;
			for( int i = 0; i < p; i ++ ) {
				if( cur % 10 >= 9 ) {
					flag = true;
					break;
				}
				else {
					cur /= 10;
					cur -= 1;
				}
			}
			if( cur ) {
				continue;
			}
			while(cur) {
				if( cur % 10 < 5 ) {
					flag = true;
					break;
				}
				cur /= 10;
			}
			if( !flag ) {
				valid = true;
				break;
			}
		}
		printf( "%s\n", (valid)? "YES": "NO" );
	}
}
