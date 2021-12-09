/*
 * loj.2086.cpp
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

#include <vector>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

const int N = 1e6 + 1e5;;
const int INF = 0x3f3f3f3f;

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
	for (; !isdigit(ch); ch = getchar())
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

int n, m, max_x;

struct SegmentTree {
	struct Node {
		int max, lazy;
	} tree[ N << 2 ];
	inline void push_up( int cur ) { tree[cur].max = Max( tree[ cur << 1 ].max, tree[ cur << 1 | 1 ].max ); }/*{{{*/
	inline void push_down( int cur ) {
		int lazy = tree[cur].lazy;
		if( lazy ) {
			tree[ cur << 1 ].max += lazy;
			tree[ cur << 1 | 1 ].max += lazy;
			tree[ cur << 1 ].lazy += lazy;
			tree[ cur << 1 | 1 ].lazy += lazy;
			tree[cur].lazy = 0;
		}
	}/*}}}*/

	void add( int from, int to, int val, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			tree[cur].max += val;
			tree[cur].lazy += val;
			return ;
		}

		push_down(cur);
		int mid = ( left + rig ) >> 1;
		if( from <= mid ) 
			add( from, to, val, cur << 1, left, mid );
		if( to > mid ) 
			add( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur); 
	}
	void add( int from, int to, int val ) { add( from, to, val, 1, 1, max_x ); }

	int query() { return tree[1].max; }
} sgt;

struct Segment { 
	int left, rig, len; 
};

int main() {
#ifdef woshiluo
	freopen( "loj.2086.in", "r", stdin );
	freopen( "loj.2086.out", "w", stdout );
#endif

	std::vector<Segment> sgs;
	std::vector<int> numbers;
	n = read<int>(); m = read<int>();

	auto len = []( int l, int r ) { return r - l; };
	for( int i = 1; i <= n; i ++ ) {
		int l, r;
		l = read<int>(); r = read<int>();
		sgs.push_back( (Segment) { l, r, len(l,r) } );
		numbers.push_back(l); numbers.push_back(r);
	}

	numbers.push_back(-1);
	sgs.push_back( (Segment) { -1, -1, 0 } );
	std::sort( sgs.begin(), sgs.end(), [] ( const Segment &_a, const Segment &_b ) { return _a.len < _b.len; });

	std::sort( numbers.begin(), numbers.end() );
	numbers.erase( std::unique( numbers.begin(), numbers.end() ), numbers.end() );
	max_x = numbers.size() + 10;

	auto get_number = [numbers]( int cur ) { return std::lower_bound( numbers.begin(), numbers.end(), cur ) - numbers.begin() + 1; };
	for( auto &seg: sgs ) {
		seg.left = get_number( seg.left );
		seg.rig = get_number( seg.rig );
	}

	int p1 = 0, p2 = 0, ans = INF;
	while( p1 < n || p2 < n ) {
		while( p2 < n && sgt.query() < m ) {
			sgt.add( sgs[p2].left, sgs[p2].rig, 1 );
			p2 ++;
		}

		if( p1 > 0 && sgt.query() >= m ) 
			chk_Min( ans, sgs[ p2 - 1 ].len - sgs[p1].len );

		sgt.add( sgs[p1].left, sgs[p1].rig, -1 );
		p1 ++;
	}

	printf( "%d\n", ans == INF? -1: ans );
}
