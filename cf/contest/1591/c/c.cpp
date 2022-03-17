/*
 * c.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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
#include <queue>
#include <vector>
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

struct Node { 
	int pos, val; 
	bool operator< ( const Node &_b ) const { 
		return pos < _b.pos;
	}
};

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n, k;
		std::vector<int> list;
		std::map<int, int> mp;
		std::priority_queue<Node> q[2];
		n = read<int>(); k = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			mp[ read<int>() ] ++;
		}
		for( auto &node: mp ) {
			if( node.first == 0 ) 
				continue;
			// TODO: Right?
			if( node.first < 0 ) 
				q[0].push( (Node) { -node.first, node.second } );
			if( node.first > 0 ) 
				q[1].push( (Node) { node.first, node.second } );
		}

		auto check_q = [&list, k]( auto q ) {
			while( !q.empty() ) {
				int pos = 0, cur_k = k;
				while( !q.empty() ) {
					Node cur = q.top(); q.pop();
					chk_Max( pos, cur.pos );
					if( cur.val <= cur_k ) {
						cur_k -= cur.val;
					}
					else {
						int cost = Min( cur.val, cur_k );
						cur.val -= cost; 
						cur_k -= cost;
						if( cur.val != 0 )
							q.push(cur);
					}
					if( cur_k == 0 )
						break;
				}
				list.push_back(pos);
			}
		};

		check_q( q[0] ); check_q( q[1] );

		std::sort( list.begin(), list.end() );

		int size = list.size();
		ll res = 0;
		for( int i = 0; i < size - 1; i ++ ) {
			res += 2 * list[i];
		}
		if( size > 0 )
			res += list.back();
		printf( "%lld\n", res );
	}
}
