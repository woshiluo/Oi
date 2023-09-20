/*
 * 1009.cpp
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

struct Package { int l, r; };

const int N = 4e5 + 1e4;

struct SegmentTree {/*{{{*/
	int n;
	struct Node { 
		int val, pos; 

		Node operator+ ( const Node &_b ) {
			Node res = (Node){ 0, 0 };
			if( val ) 
				res = (*this);
			else if( _b.val )
				res = _b;
			return res;
		}

	} tree[ N << 2 ];
	void push_up( cint cur ) { tree[cur] = tree[ cur << 1 ] + tree[ cur << 1 | 1 ]; }

	void build( cint cur, cint left, cint rig ) {/*{{{*/
		tree[cur] = (Node){ 0, 0 };
		if( left == rig ) {
			tree[cur].pos = left;
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
	}
	void init( cint _n ) { n = _n; build( 1, 1, n ); }/*}}}*/

	void add( cint pos, cint val, cint cur, cint left, cint rig ) {/*{{{*/
		if( left == rig && pos == left ) {
			tree[cur].val += val;
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		if( pos <= mid ) 
			add( pos, val, cur << 1, left, mid );
		if( pos > mid ) 
			add( pos, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void add( cint pos, cint val ) { add( pos, val, 1, 1, n ); }/*}}}*/

	Node query( cint from, cint to, cint cur, cint left, cint rig ) {/*{{{*/
		if( from <= left && rig <= to ) 
			return tree[cur];

		cint mid = ( left + rig ) >> 1;
		Node lpart = (Node){ 0, 0 }, rpart = (Node) { 0, 0 };

		if( from <= mid ) 
			lpart = query( from, to, cur << 1, left, mid );
		if( to > mid ) 
			rpart = query( from, to, cur << 1 | 1, mid + 1, rig );

		return lpart + rpart;
	}
	Node query( cint from, cint to ) { return query( from, to, 1, 1, n ); }/*}}}*/
} sgt;/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "1009.in", "r", stdin );
	freopen( "1009.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint k = read<int>();
		std::vector<int> nums;
		std::vector<Package> packs;
		for( int i = 1; i <= n; i ++ ) {
			cint l = read<int>();
			cint r = read<int>();
			nums.push_back(l);
			nums.push_back(r);
			packs.push_back( (Package) { l, r } );
		}

		std::sort( nums.begin(), nums.end() );
		nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );
		auto find_eq = [&nums]( cint cur ) {
			cint p = std::lower_bound( nums.begin(), nums.end(), cur ) - nums.begin() + 1;
			return p;
		};

		sgt.init( nums.size() );

		for( auto &pack: packs ) {
			pack.l = find_eq( pack.l );
			pack.r = find_eq( pack.r );
		}

		int ans = 0;
		std::sort( packs.begin(), packs.end(), []( const Package &_a, const Package &_b ) { return _a.r < _b.r; } );
		for( auto &pack: packs ) {
			SegmentTree::Node res = sgt.query( pack.l, pack.r );
			if( res.val == 0 ) {
				ans ++;
				sgt.add( pack.r, k - 1 );
			}
			else
				sgt.add( res.pos, -1 );
		}

		printf( "%d\n", ans );
	}
}
