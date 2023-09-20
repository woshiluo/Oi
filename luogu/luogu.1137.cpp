/*
 * luogu.1137.cpp
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

const int N = 1e5 + 1e4;

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

int main() {
#ifdef woshiluo
	freopen( "luogu.1137.in", "r", stdin );
	freopen( "luogu.1137.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();

	static int f[N], in_degree[N];

	for( int i = 1; i <= m; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();

		add_edge( u, v );
		in_degree[v] ++;
	}

	std::queue<int> q;
	for( int i = 1; i <= n; i ++ ) {
		if( in_degree[i] == 0 ) {
			f[i] = 1;
			q.push(i);
		}
	}

	while( !q.empty() ) {
		cint cur = q.front(); q.pop();
		for( int i = ehead[cur]; i; i = e[i].next ) {
			cint to = e[i].to;
			in_degree[ to ] --;
			chk_Max( f[to], f[cur] + 1 );

			if( in_degree[to] == 0 ) 
				q.push(to);
		}
	}

	for( int i = 1; i <= n; i ++ ) 
		printf( "%d\n", f[i] );
}
