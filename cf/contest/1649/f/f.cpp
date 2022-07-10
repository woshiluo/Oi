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

const int N = 5e5 + 1e4;
const ll LLF = 0x3f3f3f3f3f3f3f3f;

template<class Node>
struct SegmentTree {
	int n;
	Node tree[ N << 2 ];

	void push_up( const int cur ) { tree[cur] = tree[ cur << 1 ] + tree[ cur << 1 | 1 ]; }

	// void build( int cur, int left, int rig, Node node[] ) {
	// 	if( left == rig ) {
	// 		tree[cur] = node[left];
	// 		return ;
	// 	};

	// 	int mid = ( left + rig ) >> 1;
	// 	build( cur << 1, left, mid, node );
	// 	build( cur << 1 | 1, mid + 1, rig, node );

	// 	push_up(cur);
	// }
	void init( int _n ) { n = _n; /*build( 1, 1, n, node );*/ }

	void set( int pos, Node val, int cur, int left, int rig ) {
		if( left == rig && left == pos ) {
			tree[cur] = val;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		if( pos <= mid ) 
			set( pos, val, cur << 1, left, mid );
		if( pos > mid ) 
			set( pos, val, cur << 1 | 1, mid + 1, rig );
		
		push_up(cur);
	}
	void set( int pos, Node val ) { set( pos, val, 1, 1, n ); }

	Node query( const int from, const int to, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			return tree[cur];
		}

		int mid = ( left + rig ) >> 1;
		if( from <= mid && to > mid ) 
			return query( from, to, cur << 1, left, mid ) 
				+ query( from, to, cur << 1 | 1, mid + 1, rig );
		if( from <= mid )
			return query( from, to, cur << 1, left, mid );
		if( to > mid ) 
			return query( from, to, cur << 1 | 1, mid + 1, rig );

		std::exit(-1);
	}
	Node query( const int from, const int to ) { return query( from, to, 1, 1, n ); }
};

struct MaxNode {
	ll cur;
	MaxNode operator+ ( const MaxNode &_b ) const { return MaxNode{ Max( cur, _b.cur ) }; }
};

struct MaxPairNode {
	ll res, left, rig;
	MaxPairNode( const ll _res, const ll _left, const ll _rig ) {
		res = _res; left = _left; rig = _rig;
	}
	MaxPairNode( const ll _left = 0, const ll _rig = 0 ) {
		left = _left; rig = _rig;
		res = left + rig;
	}
	MaxPairNode operator+ ( const MaxPairNode &_b ) const { 
		return MaxPairNode{ Max( Max( res, _b.res ), left + _b.rig ),
			Max( left, _b.left ),
			Max( rig, _b.rig ) }; 
	}
};

int c[4][N];
ll l[N], r[N];

struct Segment { 
	int from, to, k; 
	bool operator< ( const Segment &_b ) const {
		if( to == _b.to ) {
			if( from == _b.from )
				return k < _b.k;
			return from < _b.from;
		}
		return to < _b.to;
	}
};

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	int n, q;
	n = read<int>(); q = read<int>();
	for( int i = 1; i <= 3; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			c[i][j] = read<int>();
		}
	}
	std::vector<Segment> segs;
	while( q -- ) {
		int x, y, k;
		x = read<int>(); y = read<int>(); k = read<int>();
		segs.push_back( (Segment){ x, y, k } );
	}

	std::sort( segs.begin(), segs.end() );
	for( int i = 1; i <= n; i ++ ) {
		l[i] = c[1][i];
		if( i > 1 ) {
			l[i] += l[ i - 1 ];
			l[i] -= c[2][ i - 1 ];
		}
	}
	for( int i = n; i >= 1; i -- ) {
		r[i] = c[3][i];
		if( i < n ) {
			r[i] += r[ i + 1 ];
			r[i] -= c[2][ i + 1 ];
		}
	}

	{
		SegmentTree<MaxNode> sgt;
		sgt.init(n);
		for( int i = 1; i <= n; i ++ ) 
			sgt.set( i, (MaxNode){ l[i] } );
		for( auto &seg: segs ) {
			ll max = sgt.query( seg.from, seg.to ).cur;
			if( seg.to + 1 > n )
				continue;
			chk_Max( l[seg.to + 1], max - seg.k );
			sgt.set( seg.to + 1, (MaxNode){ l[seg.to + 1] } );
		}
	}

	ll ans = -LLF;
	{
		SegmentTree<MaxPairNode> sgt;
		sgt.init(n);
		for( int i = 1; i <= n; i ++ ) {
			sgt.set( i, MaxPairNode( l[i], r[i] ) );
		}
		for( auto &seg: segs ) {
			chk_Max( ans, sgt.query( seg.from, seg.to ).res - seg.k );
		}
	}

	for( int i = 1; i <= n; i ++ ) 
		ans += c[2][i];
	
	printf( "%lld\n", ans );

}
