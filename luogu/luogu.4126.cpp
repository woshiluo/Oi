/*
 * luogu.4126.cpp
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

#include <stack>
#include <queue>
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

const int N = 4100;
const int M = 6e4 + 1e3;

// const int N = 210;
// const int M = 5100;

const int INF = 0x3f3f3f3f;

namespace Dinic {
	struct Edge {/*{{{*/
		int from, to, next, flow;
	} e[ M << 1 ];
	int ehead[N], chead[N], ecnt = 1;
	void add_edge( cint cur, cint to, cint flow ) {
		ecnt ++;
		e[ecnt].from = cur;
		e[ecnt].to = to;
		e[ecnt].next = ehead[cur];
		e[ecnt].flow = flow;
		ehead[cur] = ecnt;
	}/*}}}*/

	int dep[N];
	bool bfs( cint st, cint ed ) {
		memset( dep, -1, sizeof(dep ) );
		std::queue<int> q;
		dep[st] = 0; q.push(st);
		while( !q.empty() ) {
			cint cur = q.front(); q.pop();
			for( int i = ehead[cur]; i; i = e[i].next ) {
				cint to = e[i].to;
				if( dep[to] != -1 ) 
					continue;
				if( e[i].flow == 0 ) 
					continue;
				dep[to] = dep[cur] + 1;
				q.push(to);
			}
		}
		return dep[ed] != -1;
	}

	ll dfs( cint cur, cint ed, int flow ) {
		if( cur == ed ) 
			return flow;
		ll res = 0;
		for( int &i = chead[cur]; i; i = e[i].next ) {
			cint to = e[i].to;
			if( dep[to] != dep[cur] + 1 ) 
				continue;
			if( flow == 0 ) 
				break;

			cint k = dfs( to, ed, Min( flow, e[i].flow ) );

			e[i].flow -= k;
			flow -= k;

			e[ i ^ 1 ].flow += k;
			res += k;
		} 
		return res;
	}

	void dinic( cint st, cint ed ) {
		while( bfs( st, ed ) ) {
			memcpy( chead, ehead, sizeof(ehead) );
			dfs( st, ed, INF );
		}
	}

	int idx = 0;
	int dfn[N], col[N], low[N];
	bool vis[N];
	std::stack<int> stack;
	void tdfs( cint cur ) {
		idx ++;
		vis[cur] = cur;
		dfn[cur] = low[cur] = idx;
		stack.push(cur);

		for( int i = ehead[cur]; i; i = e[i].next ) {
			cint to = e[i].to;
			if( e[i].flow == 0 ) 
				continue;
			if( !dfn[to] ) {
				tdfs(to);
				chk_Min( low[cur], low[to] );
			}
			else if( vis[to] ) {
				chk_Min( low[cur], dfn[to] );
			}
		}

		if( dfn[cur] == low[cur] ) {
			while( !stack.empty() ) {
				cint top = stack.top(); stack.pop();
				col[top] = dfn[cur];
				vis[top] = false;
				if( top == cur )  
					break;
			}
		}
	}
	void tarjan( cint n ) {
		for( int i = 1; i <= n; i ++ ) 
			if( !dfn[i] ) 
				tdfs(i);
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.4126.in", "r", stdin );
	freopen( "luogu.4126.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();
	cint st = read<int>();
	cint ed = read<int>();

	for( int i = 1; i <= m; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();
		cint w = read<int>();

		Dinic::add_edge( u, v, w );
		Dinic::add_edge( v, u, 0 );
	}

	Dinic::dinic( st, ed );
	Dinic::tarjan(n);

	for( int i = 2; i <= Dinic::ecnt; i += 2 ) {
		cint u = Dinic::e[i].from;
		cint v = Dinic::e[i].to;
		cint w = Dinic::e[i].flow;
		cint u2 = Dinic::e[ i + 1 ].from;
		cint v2 = Dinic::e[ i + 1 ].to;
		cint w2 = Dinic::e[ i + 1 ].flow;

		if( w == 0 && Dinic::col[u] != Dinic::col[v] ) 
			printf( "1 " );
		else
			printf( "0 " );

		if( w == 0 && Dinic::col[u] == Dinic::col[st] && Dinic::col[v] == Dinic::col[ed] ) 
			printf( "1" );
		else if( w2 == 0 && Dinic::col[v2] == Dinic::col[st] && Dinic::col[u2] == Dinic::col[ed] ) 
			printf( "1" );
		else
			printf( "0" );

		printf( "\n" );
	}
}
