/*
 * loj.2033.cpp
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

#include <map>
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


ll ans = 0;
struct SAM {
	struct Node {
		Node *link;
		int len;
		std::map<int, Node*> nxt;
		Node() { link = 0; len = 0; }
		void update_link( Node *new_link ) {
			if( link != 0 ) 
				ans -= len - link -> len;
			link = new_link;
			ans += len - link -> len;
		}
	};
	Node *last, *rt;
	SAM() { rt = last = new Node(); }
	void extend( const int val ) {
		Node *cur = new Node();
		cur -> len = last -> len + 1;
		Node *p = last;
		while( p != 0 && p -> nxt.count(val) == 0 ) {
			p -> nxt[val] = cur;
			p = p -> link;
		} 
		if( p == 0 ) {
			cur -> update_link(rt);
		}
		else {
			Node *q = p -> nxt[val];
			if( p -> len + 1 == q -> len ) {
				cur -> update_link(q);
			}
			else {
				Node *clone = new Node();
				*clone = *q;
				clone -> len = p -> len + 1;
				while( p != 0 && p -> nxt[val] == q ) {
					p -> nxt[val] = clone;
					p = p -> link;
				}
				clone -> link = 0; clone -> update_link( q -> link );
				q -> update_link(clone);
				cur -> update_link(clone);
			}
		}
		last = cur;
	}
} sam;

int main() {
#ifdef woshiluo
	freopen( "loj.2033.in", "r", stdin );
	freopen( "loj.2033.out", "w", stdout );
#endif

	int n;
	n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		sam.extend( read<int>() );
		printf( "%lld\n", ans );
	}

}
