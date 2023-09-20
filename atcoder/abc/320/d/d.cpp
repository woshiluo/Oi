/*
 * d.cpp 2023-09-17
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
const int M = N;

struct Edge {
	int to, next, dx, dy;
} e[ M << 1 ];
int ehead[N], ecnt;
void add_edge( cint from, cint to, cint dx, cint dy ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	e[ecnt].dx = dx;
	e[ecnt].dy = dy;
	ehead[from] = ecnt;
}

ll x[N], y[N];
bool vis[N];

void dfs( cint cur ) {
	if( vis[cur] ) 
		return ;
	vis[cur] = true;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;

		x[to] = x[cur] + e[i].dx;
		y[to] = y[cur] + e[i].dy;

		dfs(to);
	}
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		cint a = read<int>();
		cint b = read<int>();
		cint x = read<int>();
		cint y = read<int>();

		add_edge( a, b, x, y );
		add_edge( b, a, -x, -y );
	}

	dfs(1);

	for( int i = 1; i <= n; i ++ ) {
		if( vis[i] )
			printf( "%lld %lld\n", x[i], y[i] );
		else
			printf( "undecidable\n" );
	}
	
}
