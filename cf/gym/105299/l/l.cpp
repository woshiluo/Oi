/*
 * l.cpp 2024-10-03
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
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ( ch - '0' );
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

const int N = 1e5 + 1e4;

struct Edge {
	i32 to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

i32 dep[N];
void dfs( ci32 cur, ci32 la ) {
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la )
			continue;
		dep[ e[i].to ] = dep[cur] + 1;
		dfs( e[i].to, cur );
	}
}

int main() {
#ifdef woshiluo
	freopen( "l.in", "r", stdin );
	freopen( "l.out", "w", stdout );
#endif
	ci32 n = read<i32>();
	ci32 m = read<i32>();
	for( int i = 1; i < n; i ++ ) {
		ci32 u = read<i32>();
		ci32 v = read<i32>();
		add_edge( u, v );
		add_edge( v, u );
	}
	if( n == 1 ) {
		i64 res = 0;
		for( int _ = 1; _ <= m; _ ++ ) {
			ci64 x = read<i64>();
			res += ( x - 1 );
			res &= 1;
		}
		if( res == 0 ) 
			printf( "Bob\n" );
		else 
			printf( "Alice\n" );
	}
	else {
		dfs( 1, 0 );
		i64 res = 0;
		for( int _ = 1; _ <= m; _ ++ ) {
			ci64 x = read<i64>();
			res ^= dep[ ( ( x - 1 ) % n ) + 1 ];
		}
		if( res == 0 ) 
			printf( "Bob\n" );
		else 
			printf( "Alice\n" );
	}
	return 0;
}
