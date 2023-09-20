/*
 * loj.3542.cpp
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

#include <set>
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

const int N = 1e5 + 1e4;

struct Seg { int a, b; };
struct Node {
	int end, id;
	bool operator< ( const Node &_b ) const { return end > _b.end; } 
};

int f[2][N];

int main() {
#ifdef woshiluo
	freopen( "loj.3542.in", "r", stdin );
	freopen( "loj.3542.out", "w", stdout );
#else
	freopen( "airport.in", "r", stdin );
	freopen( "airport.out", "w", stdout );
#endif
	int n, m1, m2;
	n = read<int>(); m1 = read<int>(); m2 = read<int>();
	std::vector<Seg> airs[2];
	for( int i = 1; i <= m1; i ++ ) {
		int a, b; 
		a = read<int>(); b = read<int>();
		airs[0].push_back( (Seg) { a, b } );
	}
	for( int i = 1; i <= m2; i ++ ) {
		int a, b; 
		a = read<int>(); b = read<int>();
		airs[1].push_back( (Seg) { a, b } );
	}
	std::set<int> set[2];
	std::sort( airs[0].begin(), airs[0].end(), []( const Seg &_a, const Seg &_b ) { return _a.a < _b.a; } );
	std::sort( airs[1].begin(), airs[1].end(), []( const Seg &_a, const Seg &_b ) { return _a.a < _b.a; } );
	int max = Max( n, Max( m1, m2 ) );
	for( int k = 0; k <= 1; k ++ ) {
		for( int i = 1; i <= max; i ++ )
			set[k].insert(i);
		std::priority_queue<Node> q;
		for( auto &air: airs[k] ) {
			while( !q.empty() && q.top().end < air.a ) {
				set[k].insert( q.top().id );
				q.pop();
			}
			int cur = *set[k].begin();
			f[k][cur] ++;
			q.push( (Node) { air.b, cur } );
			set[k].erase( set[k].begin() );
		}
		for( int i = 1; i <= max; i ++ )
			f[k][i] += f[k][ i - 1 ];
	}
	int ans = 0;
	for( int i = 0; i <= n; i ++ ) {
		chk_Max( ans, f[0][i] + f[1][ n - i ] );
	}
	printf( "%d\n", ans );
}
