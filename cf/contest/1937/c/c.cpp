/*
 * c.cpp 2024-03-01
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

char query( ci32 a, ci32 b, ci32 c, ci32 d ) {
	printf( "? %d %d %d %d\n", a, b, c, d );
	fflush(stdout);
	char op[3];
	scanf( "%s", op);
	return op[0];
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		i32 max_pos = 0;
		for( int i = 1; i < n; i ++ ) {
			if( query( max_pos, max_pos, i, i ) == '<' ) {
				max_pos = i;
			}
		}
		std::vector<i32> max_js;
		max_js.push_back(0);
		for( int i = 1; i < n; i ++ ) {
			const char result =  query( max_pos, i, max_pos, max_js.back());
			if( result == '>' ) {
				max_js.resize(0);
				max_js.push_back(i);
			}
			if( result == '=' ) {
				max_js.push_back(i);
			}
		}
		i32 min_j = max_js[0];
		for( auto &x: max_js ) {
			if( query( min_j, min_j, x, x ) == '>' ) 
				min_j = x;
		}
		printf( "! %d %d\n", max_pos, min_j );
		fflush(stdout);
	}
}
