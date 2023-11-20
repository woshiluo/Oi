/*
 * b.cpp 2023-10-22
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
const int M = 1e6 + 1e5;

struct Edge {
	int to, next, val;
} e[M];
int ehead[N], ecnt;
void add_edge( cint from, cint to, cint val ) {
	ecnt ++;
	e[ecnt].val = val;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	cint n = read<int>();
	cint t = read<int>();
	for( int o = 1; o <= t; o ++ ) {
		cint m = read<int>();
		for( int i = 1; i <= m; i ++ ) {
			cint u = read<int>();
			cint v = read<int>();
			add_edge( u, v, o );
			add_edge( v, u, o );
		}
	}

	cint k = read<int>();
	std::vector<std::vector<int>> list( t + 1 );
	for( int i = 1; i <= k; i ++ ) {
		cint x = read<int>();
		list[x].push_back(i);
	}
	for( int i = 1; i <= t; i ++) { 
		list[i].push_back( k + 10 );
	}

	struct Node {
		int val, cur;
		bool operator< ( const Node &_b ) const {
			return val > _b.val;
		}
	};
	std::priority_queue<Node> q;
	std::vector<int> dis( n + 1, k + 10 );
	std::vector<bool> vis( n + 1 );
	dis[1] = 1;
	q.push( (Node) { 1, 1 } );
	for( int o = 1; o <= k; o ++ ) {
		while( !q.empty() && q.top().val <= o ) {
			cint cur = q.top().cur; q.pop();
			if( vis[cur] ) 
				continue;
			vis[cur] = true;
			for( int i = ehead[cur]; i; i = e[i].next ) {
				cint gid = e[i].val;
				cint val = *std::lower_bound( list[gid].begin(), list[gid].end(), o );
				if( dis[ e[i].to ] > val ) {
					dis[ e[i].to ] = val + 1;
					q.push( (Node) { dis[ e[i].to ], e[i].to } );
				}
			}
		}
	}

	if( dis[n] == k + 10 ) 
		printf( "-1\n" );
	else
		printf( "%d\n", dis[n] - 1 );
}
