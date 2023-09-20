/*
 * luogu.1155.cpp
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

#include <stack>
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

const int N = 1100;

struct Edge {
	int to, next;
} e[ N * N * 2 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

inline void no_sol() {
	printf( "0" );
	std::exit(0);
}

int a[N], min[N], col[N];
void dfs( int cur, int la ) {
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la ) 
			continue;
		if( col[to] != 0 ) {
			if( col[to] != ( 3 - col[cur] ) ) 
				no_sol();
			continue;
		}
		col[to] = ( 3 - col[cur] );
		dfs( to, cur );
	}
}

std::stack<int> st[2];
int p = 1;
void pop_st( int cur ) {
	if( !st[cur].empty() && st[cur].top() != p ) 
		pop_st( cur ^ 1 );
	p ++;
	printf( "%s ", ( cur == 0 )? "b": "d" );
	st[cur].pop();
}

void push_st( int cur, int gol ) {
	printf( "%s ", ( gol == 0 )? "a": "c" );
	st[gol].push(cur);
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1155.in", "r", stdin );
	freopen( "luogu.1155.out", "w", stdout );
#endif

	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	min[ n + 1 ] = n + 1;
	for( int i = n; i >= 1; i -- ) 
		min[i] = Min( min[ i + 1 ], a[i] );
	for( int i = 1; i <= n; i ++ ) {
		for( int j = i + 1; j <= n; j ++ ) {
			if( min[ j + 1 ] < a[i] && a[i] < a[j] ) {
				add_edge( i, j );
				add_edge( j, i );
			}
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		if( !col[i] ) {
			col[i] = 1;
			dfs( i, 0 );
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		int cur = a[i], gol = col[i] - 1;
		if( gol == 1 ) {
			while( !st[0].empty() && st[0].top() == p ) 
				pop_st(0);
		}
		while( !st[gol].empty() && st[gol].top() < cur ) 
			pop_st(gol);
		while( !st[0].empty() && st[0].top() == p ) 
			pop_st(0);

		push_st( cur, gol );
	}
	while( p <= n ) {
		while( !st[0].empty() && st[0].top() == p ) 
			pop_st(0);
		while( !st[1].empty() && st[1].top() == p ) 
			pop_st(1);
	}
}
