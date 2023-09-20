/*
 * 1012.cpp
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
#include <queue>
#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef const ll cll;
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

struct Node { int a; ll s; };

int main() {
#ifdef woshiluo
	freopen( "1012.in", "r", stdin );
	freopen( "1012.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		struct Op {
			ll time;
			int op, id;
			// op = 1 insert
			// op = 2 delete
			bool operator< ( const Op &_b ) const {
				if( time == _b.time ) 
					return op < _b.op;
				return time > _b.time;
			}
		};
		std::vector<Node> nodes;
		std::vector<std::queue<ll>> q;
		std::priority_queue<Op> ops;
		std::set<std::pair<int, int>> set;

		cint n = read<int>(); cint m = read<int>();
		q.resize(m);
		for( int i = 0; i < m; i ++ ) {
			set.insert( std::make_pair( q[i].size(), i ) );
		}
		for( int i = 1; i <= n; i ++ ) {
			cint a = read<int>();
			cint s = read<int>();
			nodes.push_back( { a, s } );
			ops.push( { a, 1, (int)nodes.size() - 1 } );
		}

		auto insert = [&]( cll time, cint qid, cint id ) {
			q[qid].push( nodes[id].s );
			set.insert( std::make_pair( q[qid].size(), qid ) );
			if( q[qid].size() == 1 ) 
				ops.push( { nodes[id].s + time, 2, qid } );
		};
		auto remove = [&]( cll time, cint qid ) {
			set.erase( std::make_pair( q[qid].size(), qid ) );
			q[qid].pop();
			set.insert( std::make_pair( q[qid].size(), qid ) );
			if( !q[qid].empty() ) 
				ops.push( { q[qid].front() + time, 2, qid } );
		};

		ll res = 0;
		while( !ops.empty() ) {
			const auto op = ops.top(); ops.pop();
			cll time = op.time;
			chk_Max( res, time );
			if( op.op == 1 ) {
				const auto cq = *set.begin();
				set.erase( set.begin() );
				insert( time, cq.second, op.id );
			}
			if( op.op == 2 ) {
				remove( time, op.id );
			}
		}
		
		printf( "%lld\n", res );
	}
}
