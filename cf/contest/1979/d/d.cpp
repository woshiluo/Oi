/*
 * d.cpp 2024-06-06
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

const i32 N = 1e5 + 1e4;

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		static char str[N];
		scanf( "%s", str + 1 );
		std::vector<i32> list(1);
		for( int i = 1; i <= n; i ++ ) {
			list.push_back( str[i] - '0' );
		}
		i32 same_cnt = 1;
		for( int i = 2; i <= n; i ++ ) {
			if( list[ n - i + 1 ] == list[n] ) 
				same_cnt ++;
			else 
				break;
		}
		i32 target = -1;
		{
			i32 cur = -1, cnt = 0;
			bool just_fin = false;
			for( int i = 1; i <= n; i ++ ) {
				if( cur == -1 )
					cur = list[i];
				if( cur == list[i] ) 
					cnt ++;
				else {
					if( just_fin && list[i] == list[n] ) {
						target = Max( i - 1 - same_cnt, 1 );
					}
					else 
						target = i - 1;
					break;
				}
				if( cnt == m ) {
					just_fin = true;
					cur ^= 1;
					cnt = 0;
				}
				else 
					just_fin = false;
			}
		}
		if( target == -1 ) {
			printf( "%d\n", n );
		}
		else {/*{{{*/
			i32 cc = 0;
			i32 pos = 1;
			i32 cp = target + 1;
			i32 cur = list[cp], cnt = 0;
			while( cc < n ) {
				if( cur != list[cp] ) 
					break;

				cnt ++;
				cc ++;
				cp += pos;

				if( cp == n + 1 ) {
					cp = target;
					pos = -1;
				}
				if( cnt == m ) {
					cur ^= 1;
					cnt = 0;
				}
			}

			if( cc == n ) {
				printf( "%d\n", target );
			}
			else 
				printf( "-1\n" );
		}/*}}}*/
	}
	
}
