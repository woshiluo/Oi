/*
 * g.cpp 2024-10-30
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

#include <queue>
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

const int N = 2e5 + 1e4;
const int M = 5e5 + 1e4;

namespace dag {
	int in_degree[N];
	struct Edge {
		i32 to, next;
	} e[ M << 1 ];
	int ehead[N], ecnt;
	void add_edge( ci32 from, ci32 to ) {
		ecnt ++;
		e[ecnt].to = to;
		in_degree[to] ++;
		e[ecnt].next = ehead[from];
		ehead[from] = ecnt;
	}

	int avi_scc( ci32 max_id ) {
		std::vector<i32> zeros;
		for( int i = 0; i < max_id; i ++ ) {
			if( in_degree[i] == 0 ) 
				zeros.push_back(i);
		}
		if( zeros.size() > 1 ) {
			printf( "No\n" );
			std::exit(0);
		}
		return zeros[0];
	}
}

namespace origin {
	struct Edge {
		i32 to, next;
	} e[ M << 1 ];
	int ehead[N], ecnt;
	void add_edge( ci32 from, ci32 to ) {
		ecnt ++;
		e[ecnt].to = to;
		e[ecnt].next = ehead[from];
		ehead[from] = ecnt;
	}

	bool vis[N];
	i32 idx, dfn[N], low[N], col[N];
	std::stack<i32> st;
	std::vector<std::vector<i32>> scc;
	void tarjan( ci32 cur ) {
		if( dfn[cur] ) 
			return ;
		idx ++;
		dfn[cur] = low[cur] = idx;
		vis[cur] = true; st.push(cur);
		for( int i = ehead[cur]; i; i = e[i].next ) {
			ci32 to = e[i].to;
			if( !dfn[to] ) {
				tarjan( e[i].to );
				chk_Min( low[cur], low[to] );
			}
			else if( vis[to] ) {
				chk_Min( low[cur], dfn[to] );
			}
		}

		if( low[cur] == dfn[cur] ) {
			ci32 id = scc.size();

			std::vector<i32> list;
			while( st.top() != cur ) {
				list.emplace_back( st.top() );
				vis[st.top()] = false;
				st.pop();
			}
			list.emplace_back(cur);
			vis[cur] = false;
			st.pop();

			scc.emplace_back(list);

			for( auto &x: list ) 
				col[x] = id;
		}
	}

	void build_new_graph() {
		for( auto &list: scc ) {
			for( auto &x: list ) {
				for( int i = ehead[x]; i; i = e[i].next ) {
					if( col[x] == col[ e[i].to ] ) 
						continue;
					dag::add_edge( col[x], col[ e[i].to ] );
				}
			}
		}
	}

	bool in_meet[N];
	std::vector<std::pair<i32, std::vector<i32>>> res;
	void work( ci32 scc_id, ci32 n, std::vector<bool> &dis ) {
		std::queue<i32> q;
		for( auto &x: scc[scc_id] ) {
			if( !dis[x] ) {
				q.push(x);
				in_meet[x] = true;
				break;
			}
		}
		while( !q.empty() ) {
			ci32 cur = q.front(); q.pop();
			std::vector<i32> list;
			for( int i = ehead[cur]; i; i = e[i].next ) {
				if( !in_meet[ e[i].to ] ) {
					list.push_back( e[i].to );
					q.push( e[i].to );
					in_meet[ e[i].to ] = true;
				}
			}
			if( list.size() > 0 ) 
				res.emplace_back( cur, list );
		}
		for( int i = 1; i <= n; i ++ ) {
			if( !in_meet[i] ) 
				std::exit(-1);
		}
		printf( "Yes\n%zu\n", res.size() );
		for( auto &[cur, list]: res ) {
			printf( "%d %zu ", cur, list.size() );
			for( auto &x: list )
				printf( "%d ", x );
			printf( "\n" );
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();
	ci32 k = read<i32>();

	std::vector<bool> dis(n + 1);
	for( int i = 1; i <= k; i ++ ) {
		dis[ read<i32>() ] = true;
	}
	for( int i = 1; i <= m; i ++ ) {
		ci32 u = read<i32>();
		ci32 v = read<i32>();
		if( !dis[u] )
			origin::add_edge( u, v );
		if( !dis[v] )
			origin::add_edge( v, u );
	}

	if( n == 1 ) {
		if( !dis[1] ) 
			printf( "No\n" );
		else {
			printf( "Yes\n" );
			printf( "1\n" );
		}
		return 0;
	}

	for( int i = 1; i <= n; i ++ ) {
		if( !origin::dfn[i] ) 
			origin::tarjan(i);
	}
	origin::build_new_graph();

	origin::work( dag::avi_scc( origin::scc.size() ), n, dis );

	return 0;
}
