/*
 * e2.cpp
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

const int N = 3e5 + 1e4;

int depth[N], d[N];

struct Edge {/*{{{*/
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/

void init() {
	ecnt = 0;
//	memset( ehead, 0, sizeof(ehead) );
//	memset( d, 0, sizeof(d) );
}

int dfs( int cur, int la, int dep ) {
	depth[cur] = dep;
	std::vector<int> list;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la )
			continue;
		list.push_back( dfs( e[i].to, cur, dep + 1 ) );
	}
	std::sort( list.begin(), list.end() );
	std::reverse( list.begin(), list.end() );
	int a, b;
	a = b = dep;
	if( list.size() >= 1 ) 
		chk_Max( a, list[0] );
	if( list.size() >= 2 ) 
		chk_Max( b, list[1] );

	int k = Min( a, b ) - 1;
	if( k >= 0 )
		d[k] = Max( d[k], a + b - 2 * dep + 1 );

	return a;
}

int main() {
#ifdef woshiluo
	freopen( "e2.in", "r", stdin );
	freopen( "e2.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		init();
		int n = read<int>();
		for( int i = 0; i <= ( n << 1 ); i ++ ) 
			ehead[i] = d[i] = 0;
		for( int i = 1; i < n; i ++ ) {
			int u, v;
			u = read<int>(); v = read<int>();
			add_edge( u, v );
			add_edge( v, u );
		}
		int max_ans = dfs( 1, 0, 0 );
		for( int i = n - 2; i >= 0; i -- ) {
			d[i] = Max( d[i], d[ i + 1 ] );
		}

		int ans = 0;
		for( int i = 1; i <= n; i ++ ) {
			while( ans < max_ans && d[ans] / 2 + i > ans ) 
				ans ++;
			printf( "%d ", ans );
		}
		printf( "\n" );
	}
}
