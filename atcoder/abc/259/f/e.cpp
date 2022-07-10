/*
 * e.cpp
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

const int N = 3e5 + 1e4;

struct Edge {/*{{{*/
	int to, next, val;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( cint cur, cint to, cint val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/

int d[N];
ll f[N][2];

struct Node { 
	ll a, b; 
	bool operator< ( const Node &_b ) const {
		return ( b - a ) > ( _b.b - _b.a ); 
	}
};
// 1 0

void dfs( cint cur, cint la ) {
	ll res = 0;
	std::vector<Node> nodes;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		if( to == la ) 
			continue;
		dfs( to, cur );
		const ll p1 = f[to][1];
		const ll p2 = Max( p1, f[to][0] + ( d[to] > 0? e[i].val: 0 ) );
		if( p1 == p2 ) 
			res += p1;
		else
			nodes.push_back( (Node) { p1, p2 } );
	}

	std::sort( nodes.begin(), nodes.end() );

	cint size = nodes.size();
	for( int i = 0; i < Min( d[cur] - 1, size ); i ++ ) 
		res += Max( 0LL, nodes[i].b );
	for( int i = Max( 0, d[cur] - 1 ); i < size; i ++ ) 
		res += Max( 0LL, nodes[i].a );

	f[cur][0] = res;
	if( (int)nodes.size() >= d[cur] && d[cur] > 0 )
		f[cur][1] = res + Max( 0LL, nodes[ d[cur] - 1 ].b - nodes[ d[cur] - 1 ].a );
	else
		f[cur][1] = res;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	cint n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		d[i] = read<int>();
	}
	for( int i = 1; i < n; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();
		cint w = read<int>();

		add_edge( u, v, w );
		add_edge( v, u, w );
	}

	dfs( 1, 0 );
	printf( "%lld\n", f[1][1] );
}
