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

const int N = 2e5 + 1e4;
const int INF = 0x7fffffff;

struct SegmentTree {/*{{{*/
	int n;
	struct Node { 
		int pos, min; 
		Node operator+ ( const Node &_b ) {
			Node res;
			if( (*this).min < _b.min ) 
				res = (*this);
			else
				res = _b;
			return res;
		}
	} tree[ N << 2 ];

	void push_up( const int cur ) { tree[cur] = tree[ cur << 1 ] + tree[ cur << 1 | 1 ]; }

	void build( cint cur, cint left, cint rig, cint val[] ) {
		if( left == rig ) {
			tree[cur] = (Node){ left, val[left] };
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid, val );
		build( cur << 1 | 1, mid + 1, rig, val );

		push_up(cur);
	}
	void init( cint _n, cint val[] ) { n = _n; build( 1, 1, n, val ); }

	Node query( cint from, cint to, cint cur, cint left, cint rig ) {
		if( from <= left && rig <= to ) {
			return tree[cur];
		}

		cint mid = ( left + rig ) >> 1;
		if( from <= mid && to > mid ) 
			return query( from, to, cur << 1, left, mid ) +
				query( from, to, cur << 1 | 1, mid + 1, rig );
		else if( from <= mid ) 
			return query( from, to, cur << 1, left, mid );
		else if( to > mid ) 
			return query( from, to, cur << 1 | 1, mid + 1, rig );

		return (Node){ 0, 0 };
	}
	Node query( cint from, cint to ) { return query( from, to, 1, 1, n ); }

	void set( cint pos, cint val, cint cur, cint left, cint rig ) {
		if( pos == left && left == rig ) {
			tree[cur] = (Node) { pos, val };
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		if( pos <= mid ) 
			set( pos, val, cur << 1, left, mid );
		if( pos > mid ) 
			set( pos, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
		return ;
	}
	void set( cint pos, cint val ) { return set( pos, val, 1, 1, n ); }
} sgt;/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		static int a[N];
		cint n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
		}

		sgt.init( n, a );

		int q = read<int>();
		while( q -- ) {
			cint l = read<int>();
			cint r = read<int>();
			std::vector<SegmentTree::Node> nums;
			for( int i = 0; i < 32; i ++ ) {
				const auto node = sgt.query( l, r );
				if( node.min == INF ) 
					break;
				sgt.set( node.pos, INF );
				nums.push_back(node);
			}

			const int size = nums.size();
			int res = nums[0].min | nums[1].min;
			for( int i = 0; i < size; i ++ ) 
				for( int j = i + 1; j < size; j ++ ) 
					chk_Min( res, nums[i].min | nums[j].min );

			printf( "%d\n", res );

			for( auto &node: nums ) {
				sgt.set( node.pos, node.min );
			}
		}
	}
}
