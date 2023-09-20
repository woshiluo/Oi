/*
 * luogu.2176.cpp
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

const int N = 110;
const int M = 5100;
const int INF = 0x3f3f3f3f;

struct Edge {
	int next, to, val;
} e[ M << 1 ];
int ehead[N], ecnt;
void add_edge( cint from, cint to, cint val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

int dij( cint st, cint ed ) {
	static bool vis[N];
	static int dis[N];

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

	return dis[ed];
}

int main() {
#ifdef woshiluo
	freopen( "luogu.2176.in", "r", stdin );
	freopen( "luogu.2176.out", "w", stdout );
#endif

	cint n = read<int>();
	cint m = read<int>();

	for( int i = 1; i <= m; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();
		cint w = read<int>();

		add_edge( u, v, w );
		add_edge( v, u, w );
	}

	cint init_dis = dij( 1, n );
	int max = 0;

	for( int i = 1; i <= ecnt; i += 2 ) {
		e[i].val <<= 1;
		e[i + 1].val <<= 1;

		cint cur_dis = dij( 1, n );
		chk_Max( max, cur_dis - init_dis );

		e[i].val >>= 1;
		e[i + 1].val >>= 1;
	}

	printf( "%d\n", max );
}
