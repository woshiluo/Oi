/*
 * d.cpp 2024-07-17
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
const int K = 22;

i64 a[N];

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

i64 f[N][K];

void dfs( ci32 cur, ci32 la ) {
	for( int k = 1; k <= K; k ++ ) {
		f[cur][k] = a[cur] * k;
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, cur );

		for( int k = 1; k < K; k ++ ) {
			i64 min = ( 1LL << 62 );
			for( int p1 = 1; p1 < K; p1 ++ ) {
				if( p1 == k ) 
					continue;
				chk_Min( min, f[ e[i].to ][p1] );
			}
			f[cur][k] += min;
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<i64>();
		}

		for( int i = 1; i < n; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			add_edge( u, v );
			add_edge( v, u );
		}

		dfs( 1, 0 );

		i64 min = ( 1LL << 62 );
		for( int k = 1; k < K; k ++ ) {
			chk_Min( min, f[1][k] );
		}
		printf( "%lld\n", min );

		memset( ehead, 0, sizeof(int) * ( n + 5 ) );
		ecnt = 0;
	}
	
}
