/*
 * b.cpp 2024-03-05
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

#include <map>
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
		i32 n = read<i32>();
		std::vector<i32> a(n + 1), l( n + 1 ), r( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<i32>();
		}
		{
			std::map<i32, i32> mp;
			i32 cur = 0;
			for( int i = 1; i <= n; i ++ ) {
				mp[ a[i] ] ++;
				while( mp[cur] != 0 ) 
					cur ++;
				l[i] = cur;
			}
		}
		{
			std::map<i32, i32> mp;
			i32 cur = 0;
			for( int i = n; i >= 1; i -- ) {
				mp[ a[i] ] ++;
				while( mp[cur] != 0 ) 
					cur ++;
				r[i] = cur;
			}
		}
		bool flag = false;
		for( int i = 2; i <= n; i ++ ) {
			if( l[ i - 1 ] == r[ i ] ) {
				flag = true;
				printf( "2\n" );
				printf( "%d %d\n", 1, i - 1 );
				printf( "%d %d\n", i, n );
				break;
			}
		}
		if( !flag ) 
			printf( "-1\n" );
	}
}
