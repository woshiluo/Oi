/*
 * loj.105.cpp
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

#include <random>
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

std::mt19937 rnd(19260817);

namespace Treap {/*{{{*/
	struct Node {
		cint pri, val;
		int size;
		bool rev;
		Node *son[2];

		Node( cint _val = 0 ): pri(rnd()), val(_val) { 
			son[0] = son[1] = 0;
			size = 1;
			rev = false;
		}

		void push_up() {
			size = 1;
			if( son[0] ) 
				size += son[0] -> size;
			if( son[1] ) 
				size += son[1] -> size;
		}

		int get_size( cint cur ) {
			if( son[cur] ) 
				return son[cur] -> size;
			return 0;
		}

		void print_mid() {
			if( son[0] ) 
				son[0] -> print_mid();
			printf( "%d ", val );
			if( son[1] ) 
				son[1] -> print_mid();
		}

		int get_min() {
			if( son[0] ) 
				return son[0] -> get_min();
			return val;
		}
		int get_max() {
			if( son[1] ) 
				return son[1] -> get_max();
			return val;
		}
	};
	typedef std::pair<Node*, Node*> pnn;

	pnn split_val( Node* cur, cint val ) {/*{{{*/
		if( cur == 0 ) 
			return { 0, 0 };

		if( cur -> val <= val ) {
			auto nxt = split_val( cur -> son[1], val );
			cur -> son[1] = nxt.first;
			cur -> push_up();
			return { cur, nxt.second };
		}
		else {
			auto nxt = split_val( cur -> son[0], val );
			cur -> son[0] = nxt.second;
			cur -> push_up();
			return { nxt.first, cur };
		}
	}/*}}}*/

	pnn split_kth( Node* cur, cint key ) {/*{{{*/
		if( cur == 0 ) 
			return { 0, 0 };

		if( cur -> get_size(0) + 1 <= key ) {
			auto nxt = split_kth( cur -> son[1], key - ( cur -> get_size(0) + 1 ) );
			cur -> son[1] = nxt.first;
			cur -> push_up();
			return { cur, nxt.second };
		}
		else {
			auto nxt = split_kth( cur -> son[0], key );
			cur -> son[0] = nxt.second;
			cur -> push_up();
			return { nxt.first, cur };
		}
	}/*}}}*/

	Node* merge( Node *c1, Node *c2 ) {/*{{{*/
		if( c1 == 0 && c2 == 0 ) 
			return 0;
		if( c1 != 0 && c2 == 0 ) 
			return c1;
		if( c1 == 0 && c2 != 0 ) 
			return c2;

		if( c1 -> pri < c2 -> pri ) {
			c1 -> son[1] = merge( c1 -> son[1], c2 );
			c1 -> push_up();
			return c1;
		}
		else {
			c2 -> son[0] = merge( c1, c2 -> son[0] );
			c2 -> push_up();
			return c2;
		}
	}/*}}}*/
};/*}}}*/

using namespace Treap;

int main() {
#ifdef woshiluo
	freopen( "loj.104.in", "r", stdin );
	freopen( "loj.104.out", "w", stdout );
#endif
	int q = read<int>();

	Treap::Node *rt = 0;
	while( q -- ) {
		cint op = read<int>();
		if( op == 1 ) {
			cint x = read<int>();
			auto pair = split_val( rt, x - 1 );
			rt = merge( pair.first, new Treap::Node(x) );
			rt = merge( rt, pair.second );
		}
		if( op == 2 ) {
			cint x = read<int>();
			auto fir = split_val( rt, x - 1 );
			auto sec = split_val( fir.second, x + 1 );

			auto mid = split_kth( sec.first, 1 );

			rt = merge( fir.first, mid.second );
			rt = merge( rt, sec.second );
		}
		if( op == 3 ) {
			cint x = read<int>();
			auto fir = split_val( rt, x - 1 );

			printf( "%d\n", fir.first? fir.first -> size + 1: 1 );

			rt = merge( fir.first, fir.second );
		}
		if( op == 4 ) {
			cint x = read<int>();

			auto fir = split_kth( rt, x - 1 );

			printf( "%d\n", fir.second -> get_min() );

			rt = merge( fir.first, fir.second );
		}
		if( op == 5 ) {
			cint x = read<int>();

			auto pair = split_val( rt, x - 1 );
			printf( "%d\n", pair.first -> get_max() );
			rt = merge( pair.first, pair.second );
		}
		if( op == 6 ) {
			cint x = read<int>();

			auto pair = split_val( rt, x );
			printf( "%d\n", pair.second -> get_min() );
			rt = merge( pair.first, pair.second );
		}
	}
}
