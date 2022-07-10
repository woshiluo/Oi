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

const int N = 5e5 + 1e4;

int a[N];
int res[N];

struct Node {
	int left, rig, id;
	bool operator< ( const Node &_b ) const {/*{{{*/
		return rig > _b.rig;
	}/*}}}*/
};
		
int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		std::vector<Node> nodes;
		for( int i = 1; i <= n; i ++ ) {
			int left = i + 1, rig = n;
			a[i] = read<int>();
			if( a[i] == 0 ) {
				left = i + 1;
				rig = n;
			}
			else {
				left = ( i / ( a[i] + 1 ) ) + 1;
				rig = ( i / a[i] );
			}
			nodes.push_back( (Node) { left, rig, i } );
		}
		std::sort( nodes.begin(), nodes.end(), []( const Node &_a, const Node &_b ) { return _a.left < _b.left; } );
		std::priority_queue<Node> q;
		int p = 0;
		for( int i = 1; i <= n; i ++ ) {
			while( p < n && nodes[p].left <= i ) {
				q.push( nodes[p] );
				p ++;
			}
			Node top = q.top(); q.pop();
			res[ top.id ] = i;
		}

		for( int i = 1; i <= n; i ++ )
			printf( "%d ", res[i] );
		printf( "\n" );
	}
}
