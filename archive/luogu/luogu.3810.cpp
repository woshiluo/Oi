/*
 * luogu.3810.cpp
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

int lowbit( const int cur ) { return cur & ( -cur ); }
struct BIT {
	int n;
	int tree[N];

	void init( int _n ) { n = _n; memset( tree, 0, sizeof(tree) ); }
	void add( int pos, int val ) {
		for( ; pos <= n; pos += lowbit(pos) )
			tree[pos] += val;
	}
	
	int sum( int pos ) {
		if( pos <= 0 ) 
			return 0;
		int res = 0;
		for( ; pos; pos -= lowbit(pos) ) 
			res += tree[pos];
		return res;
	}

	int sum( int from, int to ) {
		return sum(to) - sum( from - 1 );
	}
} bit;

struct Node { int id, a, b, c; };

void calc( const int left, const int rig, const std::vector<Node> &nodes, std::vector<int> &ans ) {
	if( left == rig ) {
		for( auto &node: nodes ) {
			ans[ node.id ] += bit.sum( node.c );
			bit.add( node.c, 1 );
		}
		for( auto &node: nodes ) {
			bit.add( node.c, -1 );
		}
		return ;
	}

	const int mid = ( left + rig ) >> 1;
	for( auto &node: nodes ) {
		if( node.b <= mid ) 
			bit.add( node.c, 1 );
		else
			ans[ node.id ] += bit.sum( node.c );
	}
	for( auto &node: nodes ) {
		if( node.b <= mid ) 
			bit.add( node.c, -1 );
	}

	std::vector<Node> lpart, rpart;
	for( auto &node: nodes ) {
		if( node.b <= mid ) 
			lpart.push_back(node);
		else
			rpart.push_back(node);
	}

	calc( left, mid, lpart, ans );
	calc( mid + 1, rig, rpart, ans );
}

int main() {
#ifdef woshiluo
	freopen( "luogu.3810.in", "r", stdin );
	freopen( "luogu.3810.out", "w", stdout );
#endif
	std::vector<Node> nodes;
	const int n = read<int>();
	const int max = read<int>();

	for( int i = 1; i <= n; i ++ ) {
		const int a = read<int>();
		const int b = read<int>();
		const int c = read<int>();
		nodes.push_back( (Node) { i, a, b, c } );
	}

	std::sort( nodes.begin(), nodes.end(), []( const Node &_a, const Node &_b ) { 
		if( _a.a == _b.a ) {
			if( _a.b == _b.b ) 
				return _a.c < _b.c; 
			return _a.b < _b.b;
		}
		return _a.a < _b.a; 
	});

	bit.init(N - 1);
	std::vector<int> ans( n + 1 );
	{
		int cnt = 0;
		for( int i = n - 1; i >= 0; i -- ) {
			if( i != n - 1 && nodes[i].b == nodes[ i + 1 ].b && nodes[i].c == nodes[ i + 1 ].c ) {
				ans[ nodes[i].id ] += cnt;
				cnt ++;
			}
			else 
				cnt = 1;
		}
	}
	calc( 1, max, nodes, ans );

	std::vector<int> pool( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
//		printf( "%d\n", ans[i] );
		pool[ ans[i] ] ++;
	}

//	printf( "\n" );

	for( int i = 0; i < n; i ++ ) 
		printf( "%d\n", pool[i] );
}
