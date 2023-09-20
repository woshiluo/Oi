/*
 * uoj.117.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>

#include <vector>
#include <algorithm>

inline bool is_digit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template<class T> 
T read() { 
	T res = 0, k = 1; char x = getchar();
	for( ; !is_digit(x); x = getchar() ) 
		if( x == '-' )
			k = -1;
	for( ; is_digit(x); x = getchar() ) 
		res = res * 10 + ( x - '0' );
	return res * k;
}/*}}}*/

const int N = 1e5 + 1e4;
const int M = 2e5 + 1e4;

struct Edge {/*{{{*/
	int to, next;
} e[ M << 1 ];
int ehead[N], ecnt = 1;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/
bool deleted[ M << 1 ];

inline void no_sol() { printf( "NO\n" ); std::exit(0); }

namespace sub1 {
	int degree[N];
	std::vector<int> ans;
	void dfs( int cur ) {
		for( int &i = ehead[cur]; i; ) {
			if( deleted[i] ) {
				ehead[cur] = e[i].next;
				continue;
			}
			int to = e[i].to;
			int tmp = i;
			deleted[i] = deleted[ i ^ 1 ] = true;

			ehead[cur] = e[i].next;

			dfs( to );
			
			ans.push_back(tmp);
		}
	}
	void calc() {
		int n, m;
		n = read<int>(); m = read<int>();
		for( int i = 1; i <= m; i ++ ) {
			int u, v;
			u = read<int>(); v = read<int>();
			degree[u] ++; degree[v] ++;
			add_edge( u, v );
			add_edge( v, u );
		}
		for( int i = 1; i <= n; i ++ ) {
			if( degree[i] & 1 )
				no_sol();
			
		}
		for( int i = 1; i <= n; i ++ ) {
			if( degree[i] ) {
				dfs(i);
				break;
			}
		}
		if( ans.size() != m ) 
			no_sol();
		printf( "YES\n" );

		std::reverse( ans.begin(), ans.end() );
		for( auto x: ans ) {
			int cur = ( x >> 1 );
			printf( "%d ", ( x & 1 )? -cur: cur );
		}
	}
}

namespace sub2 {
	int in[N], out[N];
	std::vector<int> ans;
	void dfs( int cur ) {
		for( int &i = ehead[cur]; i; ) {
			if( deleted[i] ) {
				ehead[cur] = e[i].next;
				continue;
			}
			int to = e[i].to;
			deleted[i] = true;
			int tmp = i;

			ehead[cur] = e[i].next;

			dfs( to );

			ans.push_back(tmp);
		}
	}
	void calc() {
		int n, m;
		n = read<int>(); m = read<int>();
		for( int i = 1; i <= m; i ++ ) {
			int u, v;
			u = read<int>(); v = read<int>();
			in[v] ++; out[u] ++;
			add_edge( u, v );
		}
		for( int i = 1; i <= n; i ++ ) {
			if( in[i] != out[i] ) 
				no_sol();
		}
		for( int i = 1; i <= n; i ++ ) {
			if( out[i] ) {
				dfs(i);
				break;
			}
		}
		if( ans.size() != m ) 
			no_sol();
		printf( "YES\n" );

		std::reverse( ans.begin(), ans.end() );
		for( auto x: ans ) {
			printf( "%d ", x - 1 );
		}
	}
}


int main() {
#ifdef woshiluo
	freopen( "uoj.117.in", "r", stdin );
	freopen( "uoj.117.out", "w", stdout );
#endif
	int T = read<int>();
	if( T == 1 ) 
		sub1::calc();
	else
		sub2::calc();
}
