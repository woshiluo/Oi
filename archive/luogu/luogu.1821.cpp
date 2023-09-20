/*
 * luogu.1821.cpp
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

const int N = 1e3 + 1e2;
const int M = 1e5 + 1e4;
const int INF = 0x3f3f3f3f;

struct RawEdge {
	int from, to, val;
} raw_edge[M];

struct Edge {
	int to, next, val;
} e[M];
int ehead[N], ecnt;
void add_edge( cint from, cint to, cint val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

void dij( int dis[], cint st ) {
	static bool vis[N];

	memset( dis, INF, sizeof(int) * N );
	memset( vis, 0, sizeof(vis) );

	struct Dis { 
		int cur, dis; 
		bool operator< ( const Dis &_b ) const {
			return _b.dis < this -> dis;
		}
	};
	std::priority_queue<Dis> heap;

	dis[st] = 0; heap.push( { st, dis[st] } );
	while( !heap.empty() ) {
		cint cur = heap.top().cur; heap.pop();
		if( vis[cur] )
			continue;
		vis[cur] = true;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			cint to = e[i].to;
			if( dis[to] > dis[cur] + e[i].val ) {
				dis[to] = dis[cur] + e[i].val;
				heap.push( { to, dis[to] } );
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1821.in", "r", stdin );
	freopen( "luogu.1821.out", "w", stdout );
#endif

	static int dis[N], re_dis[N];

	cint n = read<int>();
	cint m = read<int>();
	cint x = read<int>();
	

	for( int i = 1; i <= m; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();
		cint w = read<int>();

		raw_edge[i] = (RawEdge){ u, v, w };
		add_edge( u, v, w );
	}

	dij( re_dis, x );

	ecnt = 0;
	memset( ehead, 0, sizeof(ehead) );
	for( int i = 1; i <= m; i ++ ) {
		add_edge( raw_edge[i].to, raw_edge[i].from, raw_edge[i].val );
	}

	dij( dis, x );

	int max = 0;

	for( int i = 1; i <= n; i ++ ) {
		if( i == x ) 
			continue;
		chk_Max( max, dis[i] + re_dis[i] );
	}

	printf( "%d\n", max );
}
