/*
 * internationale.cpp
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

/*{{{*/
struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( cint cur, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/

int dep[N], son[N];

void dfs( cint cur, cint la ) {
	dep[cur] = dep[la] + 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, cur );
	}
}

void dfs2( cint cur, cint la ) {
	std::vector<int> list;
	for( int i = ehead[cur]; i; 
}

int main() {
	freopen( "internationale.in", "r", stdin );
	freopen( "internationale.out", "w", stdout );

	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		for( int i = 1; i < n; i ++ ) {
			cint u = read<int>() + 1;
			cint v = read<int>() + 1;
			add_edge( u, v );
			add_edge( u, v );
		}
	}

	dfs( 1, 0 );
	dfs2( 1, 0 );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
