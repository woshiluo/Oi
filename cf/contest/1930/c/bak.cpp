/*
 * c.cpp 2024-02-17
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/


const int N = 3e5 + 1e4;
const int INF = 0x3f3f3f3f;

struct SegmentTree {
	int n;
	struct Node {
		int max, pos, lazy;
	} tree[ N << 2 ];
	void push_up( int cur ) { 
		if( tree[ cur << 1 ].max >= tree[ cur << 1 | 1 ].max )  {
			tree[cur].max = tree[ cur << 1 ].max;
			tree[cur].pos = tree[ cur << 1 ].pos;
		}
		else {
			tree[cur].max = tree[ cur << 1 | 1 ].max;
			tree[cur].pos = tree[ cur << 1 | 1 ].pos;
		}
	}
	void push_down( int cur ) {
		if( tree[cur].lazy ) {
			int lazy = tree[cur].lazy;
			tree[ cur << 1 ].lazy += lazy;
			tree[ cur << 1 | 1 ].lazy += lazy;
			tree[ cur << 1 ].max += lazy;
			tree[ cur << 1 | 1 ].max += lazy;
			tree[cur].lazy = 0;
		}
	}

	void build( int cur, int left, int rig ) {
		tree[cur].max = 0; tree[cur].lazy = 0;
		tree[cur].pos = rig;
		if( left == rig ) 
			return ;

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void init( int _n ) { n = _n; build( 1, 0, n ); }

	void add( int from, int to, int val, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			tree[cur].max += val; tree[cur].lazy += val;
			return ;
		}
		
		int mid = ( left + rig ) >> 1;
		push_down(cur);
		if( from <= mid ) 
			add( from, to, val, cur << 1, left, mid );
		if( to > mid ) 
			add( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void add( int from, int to, int val ) { return add( from, to, val, 1, 0, n ); }

	int get_max() { return tree[1].max; }
	int get_max_pos() { return tree[1].pos; }
} sgt;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		sgt.init(n);
		for( int i = 1; i <= n; i ++ ) {
			sgt.add( i, i, read<i32>() + i );
		}
		std::vector<i32> a;
		for( int i = 1; i <= n; i ++ ) {
			a.push_back( sgt.get_max() );
			ci32 pos = sgt.get_max_pos();
			sgt.add( pos, pos, -INF );
			if( pos + 1 <= n ) 
				sgt.add( pos + 1, n, -1 );
		}
		for( auto &x: a ) 
			printf( "%d ", x ) ;
		printf( "\n" );
	}
}
