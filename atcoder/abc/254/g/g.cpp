/*
 * g.cpp
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

const int N = 2e5 + 1e4;
const int K = 20;

struct Node { int id, left, rig; };
std::vector<Node> col[N];
Node ori[N];

int f[N][K], nxt[N][K];

int main() {
	cint n = read<int>();
	cint m = read<int>();
	cint q = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		cint p = read<int>();
		cint x = read<int>();
		cint y = read<int>();
		col[p].push_back( (Node) { i, x, y } );
		ori[i] = col[p].back();
	}


	for( int i = 1; i <= n; i ++ ) {
		std::vector<Node> list;
		list = col[i]; col[i].clear();
		std::sort( list.begin(), list.end(), []( const Node &_a, const Node &_b ) { return _a.left < _b.left; } );
		Node cur = { 0, 0, 0 };
		for( auto &node: list ) {
			if( node.rig < cur.left ) {
				col[i].push_back(cur);
				cur = node;
			}
			else 
				chk_Max( cur.rig, node.rig );
		}
		for( auto &node: list ) 
			col[0].push_back(node);
	}

	std::vector<Node> fkey = col[0];
	std::vector<Node> skey = col[0];
	std::sort( fkey.begin(), fkey.end(), []( const Node &_a, const Node &_b ) { return _a.left < _b.left; } );
	std::sort( skey.begin(), skey.end(), []( const Node &_a, const Node &_b ) { return _a.rig < _b.rig; } );

	cint size = fkey.size();
	{
		int p = -1;
		int max_id = 0;
		for( int i = 0; i < size; i ++ ) {
			while( p < size && fkey[p].left < skey[i].rig ) {
				if( fkey[p].rig > ori[max_id].rig ) 
					max_id = p;
				p ++;
			}
			f[i][0] = skey[i].rig;
			nxt[i][0] = max_id;
		}
	}

	for( int k = 1; k < K; k ++ ) {
		for( int i = 1; i <= n; i ++ ){
			f[i][k] = f[ nxt[i][ k - 1 ] ][ k - 1 ];
			nxt[i][k] = nxt[ nxt[i][ k - 1 ] ][ k - 1 ];
		}
	}

	for( int i = 1; i <= q; i ++ ) {
		cint a = read<int>();
		cint b = read<int>();
		cint c = read<int>();
		cint d = read<int>();
	}
}
