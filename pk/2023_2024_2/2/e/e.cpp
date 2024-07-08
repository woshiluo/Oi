/*
 * e.cpp 2024-03-10
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

const int N = 1e5 + 1e4;
const int K = 21;

struct Edge {
	i32 next, to;
} e[N];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

i32 max_dep = 0;
i64 mem[N][K];
i32 size[N], mson[N], dep[N];
void dfs( ci32 cur ) {
	size[cur] = 1;
	chk_Max( max_dep, dep[cur] );
	for( int i = ehead[cur]; i; i = e[i].next ) {
		dep[ e[i].to ] = dep[cur] + 1;
		dfs( e[i].to );
		size[cur] += size[ e[i].to ];
		if( size[ e[i].to ] > size[ mson[cur] ] )
			mson[cur] = e[i].to;
	}
}

i32 tar[N], son[N][K], scnt[N][K], depcnt[N];
void dfs2( ci32 cur, bool flush, bool vaild ) {
	depcnt[ dep[cur] ] ++;
	tar[ dep[cur] ] = cur;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( mson[cur] == e[i].to ) 
			continue;
		dfs2( e[i].to, true, true );
	}
	dfs2( mson[cur], false, true );
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( mson[cur] == e[i].to ) 
			continue;
		dfs2( e[i].to, false, false );
	}
	if( vaild ) {
		for( int k = 0; k < K; k ++ ) {
			if( dep[cur] + ( 1 << k ) < N ) {
				son[cur][k] = tar[ dep[cur] + ( 1 << k ) ];
				scnt[cur][k] = depcnt[ dep[cur] + ( 1 << k ) ];
			}
		}
	}
	if( flush ) {
		for( int i = dep[cur]; i <= max_dep; i ++ ) {
			depcnt[i] = 0;
			tar[i] = 0;
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 q = read<i32>();
		for( int i = 1; i < n; i ++ ) {
			add_edge( read<i32>(), i );
		}
		dfs(1);
		dfs2(1, false, true);
		for( int _ = 1; _ <= q; _ ++ ) {
			ci32 x = read<i32>();
			ci32 k = read<i32>();
			ci32 v = read<i32>();
			ci64 tot = 1LL * v * son[x][k];
			ci32 cur = son[x][k];
			if( size[x][k] 
			for( int p = k; p < K; p ++ ) {
				mem[x][ p + 1 ] += tot;
			}
		}
	}
}
