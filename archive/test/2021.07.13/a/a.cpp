/*
 * a.cpp
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

#include <vector>
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
	for (; !isdigit(ch); ch = getchar())
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

const int N = 5e5 + 1e4;

// Edge Start
struct Edge {/*{{{*/
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt = 1;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/
// Edge End

int n;
int val[N];
int ans[N];
int f[N];

void dfs( int cur, int la ) {
	f[cur] = val[cur];
	int mx1 = val[cur], mx2 = val[cur];
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la )
			continue;
		dfs( to, cur );
		if( f[to] >= mx1 ) {
			mx2 = mx1; mx1 = f[to];
		}
		else
			chk_Max( mx2, f[to] );
	}
	chk_Max( f[cur], mx2 );
}

void dfs_2( int cur, int la, int la_f ) {
	std::vector<int> a;
	a.push_back(la_f);
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la )
			continue;
		a.push_back( f[ e[i].to ] );
	}

	std::sort( a.begin(), a.end() );
	int size = a.size();
	int mx1 = ( size >= 1? a.back(): 0 ), 
		mx2 = ( size >= 2? a[ size - 2 ]: 0 ),
		mx3 = ( size >= 3? a[ size - 3 ]: 0 );


	ans[cur] = Max( val[cur], mx1 );

	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la )
			continue;
		dfs_2( e[i].to, cur, Max( val[cur], f[ e[i].to ] == mx2? mx3: mx2 ) );
	}
}



int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		val[i] = read<int>();
	}

	for( int i = 1; i < n; i ++ ) {
		int u, v;
		u = read<int>(); v = read<int>();
		add_edge( u, v );
		add_edge( v, u );
	}

	dfs( 1, 0 );
	dfs_2( 1, 0, 0 );

	for( int i = 1; i <= n; i ++ ) {
		printf( "%d ", ans[i] );
	}
}
