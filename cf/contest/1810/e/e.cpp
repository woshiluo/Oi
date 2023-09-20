/*
 * e.cpp 2023-08-26
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <set>
#include <queue>
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

const int N = 2e5 + 1e4;

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( cint from, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

int vis[N];
void init( cint n ) {
	ecnt = 0;
	memset( ehead, 0, sizeof(int) * ( n + 1 ) );
	memset( vis, 0, sizeof(int) * ( n + 1 ) );
}

int bfs( cint st, std::vector<int> &a ) {
	struct Node { 
		int val, node;
		bool operator< ( const Node &_b ) const {
			if( val == _b.val ) 
				return node < _b.node;
			return val > _b.val;
		}
	};
	std::priority_queue<Node> q;

	std::set<int> set;
	set.insert(st);
	q.push( (Node) { a[st], st } );

	int size = 0;
	while( !q.empty() ) {
		Node top = q.top(); q.pop();
		cint cur = top.node;
		if( size < top.val ) 
			break;
		vis[cur] = st;
		size ++;

		for( int i = ehead[cur]; i; i = e[i].next ) {
			cint to = e[i].to;
			if( vis[to] < st && !set.count(to) ) {
				set.insert(to);
				q.push( (Node) { a[to], to } );
			}
		}
	}

	return size;
}

void work() { 
	cint n = read<int>();
	cint m = read<int>();

	init(n);
	std::vector<int> a( n + 1 );

	{/*{{{*/
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
		}

		for( int i = 1; i <= m; i ++ ) {
			cint u = read<int>();
			cint v = read<int>();

			add_edge( u, v );
			add_edge( v, u );
		}
	}/*}}}*/

	for( int i = 1; i <= n; i ++ ) {
		if( a[i] == 0 && !vis[i] && bfs(i, a) == n ) {
			printf( "YES\n" );
			return ;
		}
	}

	printf( "NO\n" );
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		work();
	}
}
