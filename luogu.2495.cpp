/*
 * luogu.2495.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

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
T pow( T a, int p ) {
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
const int INF = 0x3f3f3f3f;

struct Edge {/*{{{*/
	int to, next, val;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( cint cur, cint to, cint val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	e[ecnt].val = val;
	ehead[cur] = ecnt;
}/*}}}*/

int idx; 
int dfn[N], dep[N];
int fa[N][K], min[N][K];
void dfs( cint cur, cint la ) {/*{{{*/
	idx ++; dfn[cur] = idx;
	fa[cur][0] = la; dep[cur] = dep[la] + 1;

	for( int k = 1; k < K; k ++ ) {
		if( fa[cur][ k - 1 ] ) {
			fa[cur][k] = fa[ fa[cur][ k - 1 ] ][ k - 1 ];
			min[cur][k] = Min( min[ fa[cur][ k - 1 ] ][ k - 1 ], min[cur][ k - 1 ] );
		}
	}

	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;

		cint to = e[i].to;
		min[to][0] = e[i].val;
		dfs( to, cur );
	}
}/*}}}*/

int get_lca( int from, int to ) {/*{{{*/
	if( dep[from] < dep[to] ) 
		std::swap( from, to );
	for( int k = K - 1; k >= 0; k -- ) {
		if( fa[from][k] && dep[ fa[from][k] ] >= dep[to] ) 
			from = fa[from][k];
	}
	if( from == to ) 
		return from;
	for( int k = K - 1; k >= 0; k -- ) {
		if( fa[from][k] && fa[to][k] && fa[from][k] != fa[to][k] ) {
			from = fa[from][k];
			to = fa[to][k];
		}
	}
	return fa[from][0];
}/*}}}*/

// should promse: lca(from,to) = from
int get_min( cint from, cint to ) {/*{{{*/
	int cur = to;
	int res = INF;
	for( int k = K - 1; k >= 0; k -- ) {
		if( fa[cur][k] && dep[ fa[cur][k] ] >= dep[from] ) {
			chk_Min( res, min[cur][k] );
			cur = fa[cur][k];
		}
	}
	return res;
}/*}}}*/

ll f[N];
bool impo[N];

void dp( cint cur ) {/*{{{*/
	f[cur] = 0;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		dp(to);
		if( impo[to] ) 
			f[cur] += e[i].val;
		else
			f[cur] += Min( f[to], (ll)e[i].val );
	}
}/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "luogu.2495.in", "r", stdin );
	freopen( "luogu.2495.out", "w", stdout );
#endif
	cint n = read<int>();
	for( int i = 1; i < n; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();
		cint w = read<int>();
		add_edge( u, v, w );
		add_edge( v, u, w );
	}

	dfs( 1, 0 );

	ecnt = 0;
	for( int i = 1; i <= n; i ++ ) 
		ehead[i] = 0;

	cint m = read<int>();
	for( int _ = 1; _ <= m; _ ++ ) {
		std::vector<int> list, set;
		int k = read<int>();
		for( int i = 1; i <= k; i ++ ) {
			list.push_back( read<int>() );
			impo[ list.back() ] = true;
		}
		std::sort( list.begin(), list.end(), []( const int &_a, const int &_b ) { return dfn[_a] < dfn[_b]; } );
		
		std::vector<int> st;
		st.push_back(1); set.push_back(1);
		
		auto try_pop = [&]() {
			cint cur = st.back(); st.pop_back();
			set.push_back(cur);
			add_edge( st.back(), cur, get_min( st.back(), cur ) );
		};
		for( auto &x: list ) {
			while(1) {
				cint lca = get_lca( x, st.back() );
				if( lca == st.back() || dfn[ st[ st.size() - 2 ] ] < dfn[lca] ) 
					break;
				try_pop();
			}

			cint lca = get_lca( x, st.back() );
			if( lca != st.back() ) {
				cint tmp = st.back(); st.pop_back();
				st.push_back(lca); st.push_back(tmp);
				try_pop();
			}
			st.push_back(x);
		}
		while( st.size() > 1 ) 
			try_pop();

		dp(1);
		printf( "%lld\n", f[1] );

		ecnt = 0;
		for( auto &x: set ) {
			ehead[x] = 0;
			impo[x] = false;
		}
	}
}
