/*
 * tree.cpp
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
#include <cstring>

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

const int N = 3e3 + 1e2;
const int INF = 0x3f3f3f3f;

struct Edge {
	int to, next, val;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to, int val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int size[N];
int f[N][N][3];

void dfs( int cur, int la ) {
	size[cur] = 1;
	f[cur][1][0] = f[cur][1][1] = 0;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to, val = e[i].val;
		if( to == la ) 
			continue;
		dfs( e[i].to, cur );
		for( int s1 = size[cur]; s1 >= 0; s1 -- ) {
			for( int s2 = size[to]; s2 >= 0; s2 -- ) {
				for( int p1 = 2; p1 >= 0; p1 -- ) {
					for( int p2 = p1; p2 >= 0; p2 -- ) {
						chk_Min( f[cur][ s1 + s2 ][p1], f[cur][s1][ p1 - p2 ] + f[to][s2][p2] + val * ( 2 - ( p2 & 1 ) ) );
					}
				}
			}
		}
		size[cur] += size[to];
	}
}

int main() {
	freopen( "tree.in", "r", stdin );
	freopen( "tree.out", "w", stdout );

	int n, k;
	n = read<int>(); k = read<int>();
	for( int i = 1; i < n; i ++ ) {
		int u, v, w;
		u = read<int>(); v = read<int>(); w = read<int>();
		add_edge( u, v, w );
		add_edge( v, u, w );
	}

	memset( f, INF, sizeof(f) );
	dfs( 1, 0 );

	int ans = INF;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j < 3; j ++ ) {
			chk_Min( ans, f[i][k][j] );
		}
	}
	printf( "%d\n", ans );
}
