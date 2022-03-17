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

int chk_pos( int cur, int pos ) { return ( cur >> pos ) & 1; }

struct Trie {
	struct Node {
		int max;
		Node *nxt[2];
		Node() {
			max = 0;
			nxt[0] = nxt[1] = 0;
		}
		void push_up() { max = Max( nxt[0]? nxt[0] -> max: 0, nxt[1]? nxt[1] -> max: 0 ); }
	};

	Node *rt;
	Trie() { rt = new Node(); }
	

	void add( Node *cur, int depth, int p, int val ) {
		if( depth == 0 ) {
			chk_Max( cur -> max, val );
			return ;
		}
		int k = chk_pos( p, depth - 1 );
		if( k ) {
			if( !cur -> nxt[1] ) 
				cur -> nxt[1] = new Node();
			add( cur -> nxt[1], depth - 1, p, val );
		}
		else {
			if( !cur -> nxt[0] ) 
				cur -> nxt[0] = new Node();
			add( cur -> nxt[0], depth - 1, p, val );
		}

		cur -> push_up();
	}

	int query( Node *cur, int depth, int p, int gol ) {
		int kp = chk_pos( p, depth - 1 ), kg = chk_pos( gol, depth - 1 );
		if( kg == 1 ) {
			if( cur -> nxt[ kp ^ 1 ] )
				return query( cur -> nxt[ kp ^ 1 ], depth - 1, p, gol );
			else
				return 0;
		}
		else {
			int max = 0;
			if( cur -> nxt[ kp ^ 1 ] ) {
				chk_Max( max, cur -> nxt[ kp ^ 1 ] -> max );
			}
			if( cur -> nxt[kp] ) {
				chk_Max( max, query( cur -> nxt[kp], depth - 1, p, gol ) );
			}
			return max;
		}
	}
} trie;


int main() {
	int n, k;
	n = read<int>(); k = read<int>();

	for( int i = 1; i <= n; i ++ ) {
	}
}
