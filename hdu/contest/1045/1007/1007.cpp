/*
 * 1007.cpp
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

#include <set>
#include <map>
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

struct Node { int id, l, r; };

const int N = 1e5 + 1e4;

int fa[N];

int get_fa( cint cur ) {
	if( fa[cur] == cur ) 
		return cur;
	return fa[cur] = get_fa( fa[cur] );
}

int main() {
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		std::vector<Node> nodes;
		for( int i = 1; i <= n; i ++ ) {
			cint l = read<int>();
			cint r = read<int>();
			fa[i] = i;
			nodes.push_back( (Node) { i, l, r } );
		}
		std::sort( nodes.begin(), nodes.end(), []( const Node &_a, const Node &_b ) { 
			if( _a.r == _b.r )
				return _a.l < _b.l; 
			return _a.r < _b.r; 
		});

		int res = 0, r = -1;
		for( auto &node: nodes ) {
			if( node.l <= r ) {
				res --;
				break;
			}
			r = node.r;
			res ++;
		}

		printf( "%d\n", res );
	}
}
