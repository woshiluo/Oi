/*
 * b.cpp 2023-08-20
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

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	struct Node { int bet, cur; };
	std::vector<Node> nodes;

	cint n = read<int>();
	std::vector<std::vector<int>> a( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		cint c = read<int>();
		a[i].resize(c);
		for( auto &x: a[i] ) 
			x = read<int>();
	}

	cint gol = read<int>();

	for( int i = 1; i <= n; i ++ ) {
		if( std::find( a[i].begin(), a[i].end(), gol ) != a[i].end() ) 
			nodes.push_back( (Node) { (int)a[i].size(), i } );
	}

	std::sort( nodes.begin(), nodes.end(), [] ( const Node &_a, const Node &_b ) { return _a.bet < _b.bet; } );

	if( nodes.size() == 0 ) {
		printf( "0" );
		return 0;
	}

	std::vector<int> res;
	cint target = nodes.front().bet;
	for( auto &node: nodes ) {
		if( node.bet == target ) 
			res.push_back( node.cur );
	}

	std::sort( res.begin(), res.end() );
	printf( "%lu\n", res.size() );
	for( auto &x: res ) 
		printf( "%d ", x );
	
}
