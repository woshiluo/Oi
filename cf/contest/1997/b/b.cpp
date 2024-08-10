/*
 * b.cpp 2024-07-31
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

const int N = 2e5 + 1e4;

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		static char buf[N];
		scanf( "%s", buf );
		std::vector<i32> list[2];
		list[0].resize(n);
		list[1].resize(n);
		for( int i = 0; i < n; i ++ ) {
			if( buf[i] == '.' ) 
				list[0][i] = 0;
			if( buf[i] == 'x' ) 
				list[0][i] = 1;
		}
		scanf( "%s", buf );
		for( int i = 0; i < n; i ++ ) {
			if( buf[i] == '.' ) 
				list[1][i] = 0;
			if( buf[i] == 'x' ) 
				list[1][i] = 1;
		}
		int res = 0;
		for( int i = 1; i < n - 1; i ++ ) {
			if( list[0][ i - 1 ] && !list[0][i] && list[0][ i + 1 ] && 
					!list[1][ i - 1 ] && !list[1][i] && !list[1][ i + 1 ] ) 
				res ++;
			if( list[1][ i - 1 ] && !list[1][i] && list[1][ i + 1 ] &&
					!list[0][ i - 1 ] && !list[0][i] && !list[0][ i + 1 ] ) 
				res ++;
		}
		printf( "%d\n",  res );
	}
	
}
