/*
 * d.cpp
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

#include <queue>
#include <algorithm>

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

struct Edge {
	int to, next;
} e[ N * N ];
int ehead[N], in[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	in[to] ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

void init() {
	for( int i = 1; i < N; i ++ ) { 
		for( int left = 1, rig; left <= i; left = rig + 1 ) {
			rig = ( i / ( i / left ) );
			if( i + ( i / left ) < N ) 
				add_edge( i, i + ( i / left ) );
		}
	}
}

int dis[N];
void bfs() {
	std::queue<int> q;
	q.push(1);
	memset( dis, 0x3f, sizeof(dis) );
	dis[1] = 0;
	while( !q.empty() ) {
		int fnt = q.front(); q.pop();
		for( int i = ehead[fnt]; i; i = e[i].next ) {
			int to = e[i].to;
			in[to] --;
			if( in[to] == 0 ) {
				q.push(to);
			}
			chk_Min( dis[to], dis[fnt] + 1 );
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	init(); bfs();
	while( T -- ) {
		int n, k;
		n = read<int>(); k = read<int>();

		static int b[N], c[N];
		for( int i = 1; i <= n; i ++ )
			b[i] = read<int>(); 
		for( int i = 1; i <= n; i ++ ) 
			c[i] = read<int>();

		struct Node { int val, mon; };
		std::vector<Node> p;
		for( int i = 1; i <= n; i ++ ) {
			p.push_back( (Node) { dis[ b[i] ], c[i] } );
		}

		static int f[ N * 20 ];
		memset( f, 0, sizeof(f) );
		int size = Min( 20 * n, k );
		for( int i = 0; i < n; i ++ ) {
			for( int j = size; j >= p[i].val; j -- ) 
				chk_Max( f[j], f[ j - p[i].val ] + p[i].mon );
		}
		printf( "%d\n", f[size] );
	}
}
