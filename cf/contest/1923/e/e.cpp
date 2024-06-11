/*
 * e.cpp 2024-03-02
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

const int N = 2e5 + 1e4;
const int K = 20;

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

int tidx = 0;
int fa[N][K], dep[N], dfn[N];
void dfs( ci32 cur, ci32 la ) {
	tidx ++;
	dfn[cur] = tidx;
	fa[cur][0] = la;
	dep[cur] = dep[la] + 1;
	for( int k = 1; k < K; k ++ ) {
		fa[cur][k] = fa[ fa[cur][ k - 1 ] ][ k - 1 ];
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la ) 
			continue;
		dfs( to, cur );
	}
}

int lca( i32 from, i32 to ) {
	if( dep[from] < dep[to] ) 
		std::swap( from, to );
	if( dep[from] != dep[to] ) {
		for( int k = K - 1; k >= 0; k -- ) {
			if( dep[ fa[from][k] ] >= dep[to] ) 
				from = fa[from][k];
		}
	}
	if( from == to ) 
		return to;
	for( int k = K - 1; k >= 0; k -- ) {
		if( fa[from][k] != fa[to][k] ) {
			from = fa[from][k];
			to = fa[to][k];
		}
	}
	return fa[from][0];
}

i64 res = 0;
i64 f[N];

void dp( ci32 cur, ci32 target, std::vector<i32> &c ) {
	bool here = ( c[cur] == target );
	f[cur] = 0;
	if( here ) 
		f[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		dp( to, target, c );
		if( here ) {
			res += f[to];
		}
		else {
			res += f[cur] * f[to];
			f[cur] += f[to];
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

		ecnt = 0;
		memset( ehead, 0, sizeof(int) * ( n + 5 ) );

		std::vector<i32> c( n + 1 );
		std::vector<std::vector<i32>> list( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			c[i] = read<i32>();
			list[ c[i] ].push_back(i);
		}
		for( int i = 1; i < n; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			add_edge( u, v );
			add_edge( v, u );
		}

		tidx = 0;
		dfs( 1, 0 );

		ecnt = 0;
		memset( ehead, 0, sizeof(int) * ( n + 5 ) );
		res = 0;

		for( int col = 1; col <= n; col ++ ) {
			if( list[col].size() <= 1 ) 
				continue;
			std::vector<i32> cur_list = list[col];
			std::sort( cur_list.begin(), cur_list.end(), [] ( const auto &_a, const auto &_b ) { return dfn[ _a ] < dfn[ _b ]; } );
			ci32 size = cur_list.size();
			for( int i = 1; i < size; i ++ ) {
				cur_list.push_back( lca( cur_list[i], cur_list[ i - 1 ] ) );
			}
			cur_list.push_back(1);
			std::sort( cur_list.begin(), cur_list.end() );
			cur_list.erase( std::unique( cur_list.begin(), cur_list.end() ), cur_list.end() );
			std::sort( cur_list.begin(), cur_list.end(), [] ( const auto &_a, const auto &_b ) { return dfn[ _a ] < dfn[ _b ]; } );

			// build virtual tree
			ecnt = 0;
			std::stack<i32> st;
			for( auto &x: cur_list ) {
				while( !st.empty() && lca( st.top(), x ) != st.top() )
					st.pop();
				if( !st.empty() ) 
					add_edge( st.top(), x );
				st.push(x);
			}

			dp( 1, col, c );

			for( auto &x: cur_list ) {
				ehead[x] = 0;
			}
		}
		printf( "%lld\n", res );
	}
}
