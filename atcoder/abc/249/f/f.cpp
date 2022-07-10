/*
 * f.cpp
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

const ll LLF = 0x3f3f3f3f3f3f3f3f;

struct Node { 
	int op, val; 
	bool operator<( const Node &_b ) const{ return val < _b.val; }
	Node reverse() {
		return (Node) { op, -val };
	}
};

std::vector<Node> nodes;
std::priority_queue<Node> q[2];

int main() {
	cint n = read<int>();
	int k = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		cint t = read<int>();
		cint val = read<int>();
		nodes.push_back( (Node){ t, val } );
	}
	ll ans = -LLF, res = 0;
	std::reverse( nodes.begin(), nodes.end() );
	for( auto &node: nodes ) {
		if( node.op == 1 && k >= 0 ) {
			while( (int)q[1].size() < k && !q[0].empty() ) {
				Node cur = q[0].top();
				if( cur.val <= 0 ) {
					break;
				}
				q[0].pop();
				res += cur.val;
				q[1].push( cur.reverse() );
			}
			while( (int)q[1].size() > k ) {
				Node cur = q[1].top(); q[1].pop();
				res += cur.val;
				q[0].push( cur.reverse() );
			}
			while( !q[0].empty() && !q[1].empty() && q[0].top().val > -q[1].top().val ) {
				Node c1 = q[0].top(); q[0].pop();
				Node c2 = q[1].top(); q[1].pop();
				res += c1.val;
				res += c2.val;
				q[0].push( c2.reverse() );
				q[1].push( c1.reverse() );
			}
			chk_Max( ans, res + node.val );
			k --;
		}
		else {
			res += node.val;
			q[0].push(node.reverse());
		}
	}
	if( k >= 0 ) {
		while( (int)q[1].size() < k && !q[0].empty() ) {
			Node cur = q[0].top();
			if( cur.val <= 0 ) {
				break;
			}
			q[0].pop();
			res += cur.val;
			q[1].push( cur.reverse() );
		}
		while( (int)q[1].size() > k ) {
			Node cur = q[1].top(); q[1].pop();
			res += cur.val;
			q[0].push( cur.reverse() );
		}
		while( !q[0].empty() && !q[1].empty() && q[0].top().val > -q[1].top().val ) {
			Node c1 = q[0].top(); q[0].pop();
			Node c2 = q[1].top(); q[1].pop();
			res += c1.val;
			res += c2.val;
			q[0].push( c2.reverse() );
			q[1].push( c1.reverse() );
		}
		chk_Max( ans, res );
	}
	printf( "%lld\n", ans );
}
