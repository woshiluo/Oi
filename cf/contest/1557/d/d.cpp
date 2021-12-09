/*
 * d.cpp
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

const int N = 6e5 + 1e4;

int n, m, tot;

struct Pair {/*{{{*/
	int pos, val;
	bool operator< ( const Pair &_b ) const { return val < _b.val; }
	bool operator> ( const Pair &_b ) const { return val > _b.val; }
};/*}}}*/
struct SegmentTree {/*{{{*/
	struct Node {
		int left, rig;
		Pair val, lazy;
	} tree[ N << 2 ];

	void push_up( int cur ) {
		tree[cur].val = Max( tree[ cur << 1 ].val, tree[ cur << 1 | 1 ].val );
	}
	void push_down( int cur ) {
		if( tree[cur].lazy.val != 0 ) {
			Pair lazy = tree[cur].lazy;
			tree[ cur << 1 ].lazy = lazy;
			tree[ cur << 1 | 1 ].lazy = lazy;
			tree[ cur << 1 ].val = lazy;
			tree[ cur << 1 | 1 ].val = lazy;
			tree[cur].lazy.val = 0;
		}
	}

	void set( int from, int to, Pair val, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			tree[cur].lazy = val; tree[cur].val = val;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		push_down(cur);
		if( from <= mid )
			set( from, to, val, cur << 1, left, mid );
		if( to > mid )
			set( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void set( int from, int to, Pair val ) { set( from, to, val, 1, 1, tot ); }

	Pair query( int from, int to, int cur, int left, int rig ) {
		if( from <= left && rig <= to  ) {
			return tree[cur].val;
		}

		int mid = ( left + rig ) >> 1;
		Pair res = { 0, 0 };
		push_down(cur);
		if( from <= mid ) 
			chk_Max( res, query( from, to, cur << 1, left, mid ) );
		if( to > mid ) 
			chk_Max( res, query( from, to, cur << 1 | 1, mid + 1, rig ) );

		push_up(cur);
		return res;
	}
	Pair query( int from, int to ) { return query( from, to, 1, 1, tot ); }
} sgt;/*}}}*/

int la[N];
Pair ans[N];
bool vis[N];

void dfs( int cur ) {
	vis[cur] = true;
	if( la[cur] == 0 ) 
		return ;
	dfs( la[cur] );
}

struct Seg {
	int l, r;
};
int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	n = read<int>(); m = read<int>();
	std::vector<Seg> segs[N]; std::vector<int> nums;
	for( int i = 1; i <= m; i ++ ) {
		int id, l, r;
		id = read<int>(); l = read<int>(); r = read<int>();
		segs[id].push_back( (Seg) { l, r } );
		nums.push_back(l); nums.push_back(r);
	}

	std::sort( nums.begin(), nums.end() );
	nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );
	tot = nums.size();
	auto find = [&nums]( const int &cur ) { return std::lower_bound( nums.begin(), nums.end(), cur ) - nums.begin() + 1; };
	for( int i = 1; i <= n; i ++ ) {
		for( auto &seg: segs[i] ) {
			seg.l = find( seg.l ); seg.r = find( seg.r );
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		Pair res = { 0, 0 };
		for( auto &seg: segs[i] ) {
			chk_Max( res, sgt.query( seg.l, seg.r ) );
		}
		if( res.val == 0 ) {
			res = { i, 1 };
			ans[i] = res;
		}
		else {
			la[i] = res.pos;
			res.pos = i; res.val ++;
			ans[i] = res;
		}
		for( auto &seg: segs[i] ) {
			sgt.set( seg.l, seg.r, res );
		}
	}

	Pair res = { 0, 0 };
	for( int i = 1; i <= n; i ++ ) {
		chk_Max( res, ans[i] );
	}
	printf( "%d\n", n - res.val );
	dfs(res.pos);
	for( int i = 1; i <= n; i ++ ) {
		if( !vis[i] ) 
			printf( "%d ", i );
	}
}
