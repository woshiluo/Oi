/*
 * f.cpp 2023-09-09
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

#include <queue>
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

const int N = 510;

struct edge {
	int to, next;
} e[N];
int ehead[N], ecnt;
void add_edge( cint from, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

struct Node {
	int cur, t, s, g; 
	bool operator< ( const Node &_b ) const {
		if( s == _b.s ) {
			if( g == _b.g )
				return cur < _b.cur;
			return g > _b.g;
		}
		return s > _b.s;
	}
} nodes[N];


int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	cint n = read<int>();
	for( int i = 2; i <= n; i ++ ) {
		cint p = read<int>();
		cint t = read<int>();
		cint s = read<int>();
		cint g = read<int>();

		add_edge( p, i );
		nodes[i] = (Node) { i, t, s, g };
	}
	nodes[1].cur = 1;
	nodes[1].g = 1;

	std::priority_queue<Node> q[2];

	ll strength = 1;
	q[0].push( nodes[1] );
	// 0 *
	// 1 +

	while( !q[0].empty() || !q[1].empty() ) {
		if( !q[1].empty() && q[1].top().s <= strength ) {
			const auto top = q[1].top(); q[1].pop();
			cint cur = top.cur;

			strength += 1LL * top.g;
			for( int i = ehead[cur]; i; i = e[i].next ) {
				cint to = e[i].to;
				q[ ( nodes[to].t == 1 ) ].push( nodes[ e[i].to ] );
			}
		}
		else if( !q[0].empty() ) {
			const auto top = q[0].top(); q[0].pop();
			cint cur = top.cur;

			strength *= 1LL * top.g;
			for( int i = ehead[cur]; i; i = e[i].next ) {
				cint to = e[i].to;
				q[ ( nodes[to].t == 1 ) ].push( nodes[ e[i].to ] );
			}
		}
		else {
			printf( "No\n" );
			return 0;
		}
	}

	printf( "Yes\n" );

}
