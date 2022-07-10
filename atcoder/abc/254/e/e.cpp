/*
 * e.cpp
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

struct Edge {/*{{{*/
	int to, next;
} e[ N << 3 ];
int ehead[N], ecnt;
void add_edge( cint cur, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/

std::set<int> set;

void dfs( cint st, cint k ) {
	std::queue<std::pair<int, int>> q;
	q.push(std::make_pair( st, k ) );
	set.insert(st);
	while( !q.empty() ) {
		auto pair = q.front(); q.pop();
		int cur = pair.first;
		if( pair.second == 0 ) 
			continue;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( !set.count( e[i].to ) ) {
				set.insert( e[i].to );
				q.push( std::make_pair( e[i].to, pair.second - 1 ) );
			}
		}
	}
}
int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	cint n = read<int>();
	cint m = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();
		add_edge( u, v );
		add_edge( v, u );
	}
	cint q = read<int>();
	for( int i = 1; i <= q; i ++ ) { 
		set.clear();
		cint x = read<int>();
		cint k = read<int>();
		dfs( x, k );

		ll res = 0;
		for( auto &p: set ) 
			res += p;
		printf( "%lld\n", res );
	}
}
