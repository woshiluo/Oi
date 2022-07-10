/*
 * h.cpp
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

const int N = 1e5 + 1e4;
const int K = 30;

int a[N], b[N];

int full_pow( cint cur ) { return 1 << cur; }
bool chk_pos( cint cur, cint pos ) { return cur & full_pow(pos); }

struct Trie {/*{{{*/
	struct Node {/*{{{*/
		int cnt;
		Node *nxt[2];

		Node() {
			nxt[0] = nxt[1] = 0;
		}

		void push_up() {
//			cnt = ( nxt[0]? nxt[0] -> cnt: 0 ) 
//				+ ( nxt[1]? nxt[1] -> cnt: 0 );
		}
	};/*}}}*/

	Node *rt;

	void insert( Node *cur, cint p, cint k ) {
		const bool kind = chk_pos( p, k );
		if( cur -> nxt[kind] == 0 ) 
			cur -> nxt[kind] = new Node();
		if( p == full_pow(k) ) {
			cur -> cnt ++;
			return ;
		}

		if( kind ) 
			insert( cur -> nxt[kind], p ^ full_pow(k), k - 1 );
		else
			insert( cur -> nxt[kind], p, k - 1 );

		cur -> push_up();
	}

	void insert( cint p ) { return insert( rt, p, K ); }

	bool try_erase( cint p ) {
		Node *cur = rt;
		std::vector<Node*> list;
		int k = K;
		while( k >= 0 && cur ) {
			if( cur -> cnt ) 
				list.push_back(cur);
			cur = cur -> nxt[ chk_pos( p, k ) ];
			k --;
		}
		if( list.size() ) 
			list.back() -> cnt --;
		return false;
	}
} trie;/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "h.in", "r", stdin );
	freopen( "h.out", "w", stdout );
#endif
	cint n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		trie.insert( a[i], 0 );
	}
	for( int i = 1; i <= n; i ++ ) {
		b[i] = read<int>();
		trie.insert( b[i], 1 );
	}

	for( int i = 1; i <= n; i ++ ) {
		if( !trie.try_erase( a[i] ) ) {
			printf( "-1\n" );
			continue;
		}
	}
}
