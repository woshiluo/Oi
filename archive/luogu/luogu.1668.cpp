/*
 * luogu.1668.cpp
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

const int N = 1e6 + 1e5;
const int INF = 0x3f3f3f3f;

struct Edge {
	int to, next, val;
} e[N];
int ehead[ N << 1 ], ecnt;
void add_edge( cint from, cint to, cint val = 1 ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	e[ecnt].val = val;
	ehead[from] = ecnt;
}

int dis[N];
void dij( cint st ) {
	static bool vis[N];

	memset( vis, 0, sizeof(vis) );
	memset( dis, INF, sizeof(dis) );

	struct Dis { 
		int cur, dis; 
		bool operator< ( const Dis &_b ) const {
			return _b.dis < this -> dis;
		}
	};
	std::priority_queue<Dis> heap;
	auto push_heap = [&]( cint cur ) { heap.push( { cur, dis[cur] } ); };

	dis[st] = 0; push_heap(st);

	while( !heap.empty() ) {
		cint cur = heap.top().cur; heap.pop();
		if( vis[cur] )
			continue;
		vis[cur] = true;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			cint to = e[i].to;
			if( dis[to] > dis[cur] + e[i].val ) {
				dis[to] = dis[cur] + e[i].val;
				push_heap(to);
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1668.in", "r", stdin );
	freopen( "luogu.1668.out", "w", stdout );
#endif

	cint n = read<int>();
	cint t = read<int>() + 1;
	for( int i = 1; i <= n; i ++ ) {
		cint u = read<int>();
		cint v = read<int>() + 1;
		add_edge( u, v );
	}
	for( int i = t; i >= 2; i -- ) {
		add_edge( i, i - 1, 0 );
	}

	dij(1);
	printf( "%d\n", dis[t] == INF? -1: dis[t] );
}
