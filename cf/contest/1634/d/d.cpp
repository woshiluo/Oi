/*
 * d.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <random>
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

std::random_device seed;
std::mt19937 rnd(seed());

int query( int a, int b, int c ) {
	printf( "? %d %d %d\n", a, b, c );
	fflush(stdout);
	int res;
	scanf( "%d", &res );
	return res;
}

void ask( int a, int b ) {
	printf( "! %d %d\n", a, b );
	fflush(stdout);
	return ;
}

struct Node { int pos, val; };

void work() {
	int n = read<int>();
	int x, y;
	x = ( rnd() % ( n - 1 ) ) + 1; 
	y = x + 1;
	std::vector<Node> a, b;
	for( int i = 1; i <= n; i ++ ) {
		if( i == x || i == y ) 
			continue;
		a.push_back( (Node) { i, query( i, x, y ) } );
	}
	std::sort( a.begin(), a.end(), []( const Node &_a, const Node &_b ) { if( _a.val == _b.val ) return _a.pos < _b.pos; return _a.val > _b.val; } );

	int p1 = a.front().pos;
	for( int i = 1; i <= n; i ++ ) {
		if( i == x || i == p1 ) 
			continue;
		b.push_back( (Node) { i, query( i, x, p1 ) } );
	}
	std::sort( b.begin(), b.end(), []( const Node &_a, const Node &_b ) { if( _a.val == _b.val ) return _a.pos < _b.pos; return _a.val > _b.val; } );

	if( b.front().val <= a.front().val ) {
		bool flag = false;
		for( auto &val: a ) {
			if( val.val != a.front().val ) 
				flag = true;
		}
		if( !flag )
			ask( x, y );
		else {
			int p = 1;
			while( p == x || p == p1 || p == y ) 
				p ++;
			if( query( p1, x, p ) == a.front().val ) 
				ask( p1, x );
			else
				ask( p1, y );
		}
		return ;
	}
	
	int p2 = b.front().pos;
	ask( p1, p2 );
	return ;
}

int main() {
	int T = read<int>();
	while( T -- ) {
		work();
	}
	return 0;
}
