/*
 * e.cpp 2024-02-29
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

#include <stack>
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
const int INF = 0x3f3f3f3f;

i32 full_pow( ci32 cur ) { return 1 << cur; }
bool chk_pos( ci32 mask, ci32 pos ) { return ( mask >> pos ) & 1; }


struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

int dfn[N], tidx = 0;
int size[N];
void dfs( ci32 cur, ci32 la ) {
	tidx ++;
	dfn[cur] = tidx;
	size[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la ) 
			continue;
		dfs( to, cur );
		size[cur] += size[to];
	}
}

i32 fa[N], dep[N];
void dfs2( ci32 cur, ci32 la ) {
	dep[cur] = dep[la] + 1;
	fa[cur] = la;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la ) 
			continue;
		dfs2( to, cur );
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

		tidx = 0;
		ecnt = 0;
		memset( ehead, 0, sizeof(int) * ( n + 5 ) );

		for( int i = 1; i < n; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			add_edge( u, v );
			add_edge( v, u );
		}

		std::vector<std::pair<i32, i32>> nodes;
		dfs2( 1, 0 );

		int k = read<i32>();
		for( int i = 1; i <= k; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			nodes.push_back( std::make_pair( u, v ) );
		}

		std::vector<i32> edge_mask( n + 5 );
		auto toggle_pair = [&] ( i32 from, i32 to, i32 mask ) {
			if( dep[from] < dep[to] ) 
				std::swap( from, to );
			while( dep[from] != dep[to] ) { 
				edge_mask[from] ^= mask;
				from = fa[from];
			}
			while( from != to ) { 
				edge_mask[from] ^= mask;
				edge_mask[to] ^= mask;
				from = fa[from];
				to = fa[to];
			}
		};

		std::vector<i32> sets;
		for( int i = 0; i < k; i ++ ) {
			auto [u, v] = nodes[i];
			toggle_pair( u, v, 1 << i);
		}
		for( int i = 1; i <= n; i ++ )
			sets.push_back( edge_mask[i] );
		std::sort( sets.begin(), sets.end() );
		sets.erase( std::unique( sets.begin(), sets.end() ), sets.end() );

		std::vector<i32> f( full_pow(k), INF );
		f[0] = 0;
		for( int mask = 0; mask < full_pow(k); mask ++ ) {
			for( auto &set: sets ) {
				chk_Min( f[ mask | set ], f[mask] + 1 );
			}
		}
		printf( "%d\n", f[ full_pow(k) - 1 ] );
	}
}
