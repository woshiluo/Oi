/*
 * luogu.4047.cpp
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */


#include <cmath>
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

const int N = 1e3 + 1e2;

struct Set {/*{{{*/
	int set[N];
	void init( cint n ) { for( int i = 0; i <= n; i ++ ) set[i] = i; }
	int get_fa( cint cur ) {
		if( set[cur] == cur )
			return cur;
		set[cur] = get_fa( set[cur] );
		return set[cur];
	}
	int& operator[]( const int cur ) { 
		return set[ get_fa(cur) ];
	}
} set;/*}}}*/

struct Node { double x, y; } nodes[N];

double dis( const Node &_a, const Node &_b ) { 
	return std::sqrt( ( _a.x - _b.x ) * ( _a.x - _b.x ) + ( _a.y  - _b.y ) * ( _a.y - _b.y ) );
}

int main() {
#ifdef woshiluo
	freopen( "luogu.4047.in", "r", stdin );
	freopen( "luogu.4047.out", "w", stdout );
#endif

	int n, k;
	scanf( "%d%d", &n, &k );
	set.init(n);

	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lf%lf", &nodes[i].x, &nodes[i].y );
	}

	struct Edge { int from, to; double val; };
	std::vector<Edge> edges;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = i + 1; j <= n; j ++ ) {
			edges.push_back( { i, j, dis( nodes[i], nodes[j] ) } );
		}
	}

	std::sort( edges.begin(), edges.end(), []( const Edge &_a, const Edge &_b ) {
		return _a.val < _b.val;
	});

	int link_cnt = 0;
	for( auto &edge: edges ) {
		cint from = edge.from;
		cint to = edge.to;

		if( set[from] != set[to] ) {
			if( link_cnt == n - k ) {
				printf( "%.2lf", edge.val );
				return 0;
			}
			set[from] = set[to];
			link_cnt ++;
		}
	}
}
