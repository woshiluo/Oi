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

const int N = 5e4 + 1e3;
const int INF = 0x3f3f3f3f;

struct SegmentTree {
	int n;
	struct Node {
		int min, lazy;
	} tree[ N << 2 ];
	void push_up( int cur ) { tree[cur].min = Min( tree[ cur << 1 ].min, tree[ cur << 1 | 1 ].min ); }
	void push_down( int cur ) {
		if( tree[cur].lazy != INF ) {
			int lazy = tree[cur].lazy;
			chk_Min( tree[ cur << 1 ].lazy, lazy );
			chk_Min( tree[ cur << 1 | 1 ].lazy, lazy );
			chk_Min( tree[ cur << 1 ].min, lazy );
			chk_Min( tree[ cur << 1 | 1 ].min, lazy );
			tree[cur].lazy = INF;
		}
	}

	void build( int cur, int left, int rig ) {
		tree[cur].min = INF; tree[cur].lazy = INF;
		if( left == rig ) 
			return ;

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void init( int _n ) { n = _n; build( 1, 0, n ); }

	void chk_min( int from, int to, int val, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			chk_Min( tree[cur].min, val );
			chk_Min( tree[cur].lazy, val );
			return ;
		}

		int mid = ( left + rig ) >> 1;
		push_down(cur);
		if( from <= mid ) 
			chk_min( from, to, val, cur << 1, left, mid );
		if( to > mid ) 
			chk_min( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void chk_min( int from, int to, int val ) { return chk_min( from, to, val, 1, 1, n ); }

	int query( int pos, int cur, int left, int rig ) {
		if( left == rig ) {
			return tree[cur].min;
		}

		int mid = ( left + rig ) >> 1;
		push_down(cur);
		if( pos <= mid ) 
			return query( pos, cur << 1, left, mid );
		if( pos > mid ) 
			return query( pos, cur << 1 | 1, mid + 1, rig );

		return INF;
	}
	int query( int pos ) {
		if( pos <= 0 ) 
			return 0;
		return query( pos, 1, 1, n ); 
	}
} sgt;


int x;
int a[N], nxt[N], f[N];

bool check( int p1, int p2 ) {
	return a[p1] + a[p2] >= 2 * x;
}

bool check( int p1, int p2, int p3 ) {
	return a[p1] + a[p2] + a[p3] >= 3 * x;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		sgt.init(n);
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
			f[i] = n + 1;
		}
		x = read<int>();
		int p2 = 1;
		for( int i = 1; i <= n; i ++ ) {
			chk_Max( p2, i );
			while( p2 + 1 <= n && check( p2, p2 + 1 ) && ( p2 - 1 < i || check( p2 - 1, p2, p2 + 1 ) ) )
				p2 ++;
			nxt[i] = p2;
		}

		sgt.chk_min( 1, n, n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			sgt.chk_min( i, i, sgt.query( i - 1 ) + 1 );
			if( i == 1 )
				sgt.chk_min( i, nxt[i], 0 );
			else
				sgt.chk_min( i, nxt[i], sgt.query( i - 2 ) + 1 );
		}
		printf( "%d\n", Max( n - sgt.query(n), n - ( n >> 1 ) ) );
	}
}
