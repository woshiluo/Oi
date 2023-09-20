/*
 * set.cpp
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

const int N = 1e6 + 1e5;

struct Node {
	int x, y;
};

struct Set {
	std::vector<int> node[2];
} set[2];

bool vis[2][N];

int main() {
#ifdef woshiluo
	freopen( "set.in", "r", stdin );
	freopen( "set.out", "w", stdout );
#endif
	int n, m;
	std::vector<Node> nodes;
	n = read<int>(); m = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		int x, y; 
		x = read<int>(); y = read<int>();
		vis[0][x] = vis[1][y] = true;
		nodes.push_back( (Node) { x, y } );
	}

	std::vector<int> freedom[2];
	for( int i = 1; i <= n; i ++ ) {
		if( !vis[0][i] ) 
			freedom[0].push_back(i);
		if( !vis[1][i] ) 
			freedom[1].push_back(i);
	}

	std::vector<int> y_list; y_list.push_back(0);
	for( auto &node: nodes ) {
		y_list.push_back( node.y );
	}
	std::sort( y_list.begin(), y_list.end() ); int mid_y = y_list[ y_list.size() >> 1 ];
	y_list.erase( std::unique( y_list.begin(), y_list.end() ), y_list.end() );

	for( auto &x: y_list ) {
		if( x <= mid_y )
			set[0].node[1].push_back(x);
		else
			set[1].node[1].push_back(x);
	}

	std::sort( nodes.begin(), nodes.end(), []( const Node &a, const Node &b ) { return a.y < b.y; } );
	for( auto &node: nodes ) {
		if( node.y <= mid_y ) 
			set[1].node[0].push_back(node.x);
		else
			set[0].node[0].push_back(node.x);
	}

	// TODO: lamda
	while( set[0].node[0].size() < set[0].node[1].size() ) {
		set[0].node[0].push_back( freedom[0].back() );
		freedom[0].pop_back();
	}
	
	while( set[0].node[0].size() > set[0].node[1].size() ) {
		set[0].node[1].push_back( freedom[1].back() );
		freedom[1].pop_back();
	}
	
	while( set[1].node[0].size() < set[1].node[1].size() ) {
		set[1].node[0].push_back( freedom[0].back() );
		freedom[0].pop_back();
	}
	
	while( set[1].node[0].size() > set[1].node[1].size() ) {
		set[1].node[1].push_back( freedom[1].back() );
		freedom[1].pop_back();
	}

	while( !freedom[0].size() ) {
		set[0].node[0].push_back( freedom[0].back() );
		set[0].node[1].push_back( freedom[1].back() );
		freedom[0].pop_back(); freedom[1].pop_back();
	}

	printf( "%ld\n", set[0].node[0].size() );
	for( auto x: set[0].node[0] ) 
		printf( "%d ", x );
	printf( "\n" );
	for( auto x: set[0].node[1] ) 
		printf( "%d ", x );
	printf( "\n" );
}
