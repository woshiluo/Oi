/*
 * d2.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

#include <set>
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

const int N = 1e5 + 1e4;

struct Set {/*{{{*/
	int n;
	int set[N], size[N];
	Set( int _n ) { n = _n; }
	void init() {
		for( int i = 0; i <= n; i ++ ) {
			set[i] = i;
			size[i] = 1;
		}
	}
	int get( int x ) {
		if( set[x] == x ) 
			return x;
		return set[x] = get( set[x] );
	}
	void merge( int x, int y ) {
		x = get(x); y = get(y);
		if( x > y ) 
			std::swap( x, y );
		size[ set[x] ] += size[ set[y] ];
		set[y] = set[x];
	}
};/*}}}*/

struct Node { int u, v; };

int main() {
#ifdef woshiluo
	freopen( "d2.in", "r", stdin );
	freopen( "d2.out", "w", stdout );
#endif
	int n, m1, m2;
	n = read<int>(); m1 = read<int>(); m2 = read<int>();
	Set fa[2] = {Set(n), Set(n)};
	fa[0].init(); fa[1].init();
	for( int i = 1; i <= m1; i ++ ) {
		int u, v;
		u = read<int>(); v = read<int>();
		fa[0].merge( u, v );
	}
	for( int i = 1; i <= m2; i ++ ) {
		int u, v;
		u = read<int>(); v = read<int>();
		fa[1].merge( u, v );
	}
	std::set<int> set[2];
	for( int i = 2; i <= n; i ++ ) {
		if( fa[0].get(i) == i ) 
			set[0].insert(i);
	}
	for( int i = 2; i <= n; i ++ ) {
		if( fa[1].get(i) == i ) 
			set[1].insert(i);
	}
	if( set[0].size() > set[1].size() ) {
		std::swap( set[0], set[1] );
		std::swap( fa[0], fa[1] );
	}
	std::vector<int> ans, less[2];
	for( int i = 1; i <= n; i ++ ) {
		if( fa[0].get(i) != 1 && fa[1].get(i) != 1 ) {
			ans.push_back(i);
			fa[0].merge( 1, i ); fa[1].merge( 1, i );
		}
	}
	for( int i = 2; i <= n; i ++ ) {
		if( fa[0].get(i) != 1 ) 
			less[0].push_back(i);
	}
	for( int i = 2; i <= n; i ++ ) {
		if( fa[1].get(i) != 1 ) 
			less[1].push_back(i);
	}
	int p0 = 0, p1 = 0;
	int size0 = less[0].size(), size1 = less[1].size();
	std::vector<Node> ans2;
	while( p0 < size0 && p1 < size1 ) {
		if( fa[0].get( less[0][p0] ) == 1 ) {
			p0 ++;
			continue;
		}
		auto check = [&fa]( const int u, const int v ) { return fa[1].get(v) != 1 && fa[0].get(v) == 1; };
		while( check( less[0][p0], less[1][p1] ) == false )
			p1 ++;
		int u = less[0][p0], v = less[1][p1];
		ans2.push_back( (Node) { less[0][p0], less[1][p1] } );
		fa[0].merge( u, v ); fa[1].merge( u, v );
		p1 ++; p0 ++;
	}
	printf( "%ld\n", ans.size() + ans2.size() );
	for( auto &x: ans ) {
		printf( "1 %d\n", x );
	}
	for( auto &x: ans2 ) {
		printf( "%d %d\n", x.u, x.v );
	}
}
