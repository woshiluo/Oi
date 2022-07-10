/*
 * tmp.cpp
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

const int N = 4e6 + 1e2;

int len( cint left, cint rig ) { return rig - left + 1; }

struct SegmentTree {
	int n;
	struct Node { 
		int sum, lazy_set; 
		bool lazy_filp;
	} tree[ N << 2 ];

	void push_down( cint cur, cint left, cint rig ) {/*{{{*/
		cint mid = ( left + rig ) >> 1;
		if( tree[cur].lazy_set != -1 ) {
			int &lazy = tree[cur].lazy_set;
			tree[ cur << 1 ].sum = len( left, mid ) * lazy;
			tree[ cur << 1 | 1 ].sum = len( mid + 1, rig ) * lazy;
			tree[ cur << 1 ].lazy_set = lazy;
			tree[ cur << 1 | 1 ].lazy_set = lazy;
			if( !tree[cur].lazy_filp ) {
				tree[ cur << 1 ].lazy_filp = false;
				tree[ cur << 1 | 1 ].lazy_filp = false;;
			}
			lazy = -1;
		}
		if( tree[cur].lazy_filp ) {
			tree[ cur << 1 ].sum = len( left, mid ) - tree[ cur << 1 ].sum;
			tree[ cur << 1 | 1 ].sum = len( mid + 1, rig ) - tree[ cur << 1 | 1 ].sum;
			tree[ cur << 1 ].lazy_filp ^= 1;
			tree[ cur << 1 | 1 ].lazy_filp ^= 1;
			tree[cur].lazy_filp ^= 1;
		}
	}/*}}}*/
	
	void push_up( cint cur ) { tree[cur].sum = tree[ cur << 1 ].sum + tree[ cur << 1 | 1 ].sum; }

	void set( cint from, cint to, cint val, cint cur, cint left, cint rig ) {/*{{{*/
		if( from <= left && rig <= to ) {
			tree[cur].lazy_set = val;
			tree[cur].sum = len( left, rig ) * val;
			tree[cur].lazy_filp = false;
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		push_down( cur, left, rig );
		if( from <= mid ) 
			set( from, to, val, cur << 1, left, mid );
		if( to > mid ) 
			set( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void set( cint from, cint to, cint val ) { return set( from, to, val, 1, 1, n ); }/*}}}*/

	void flip( cint from, cint to, cint cur, cint left, cint rig ) {/*{{{*/
		if( from <= left && rig <= to ) {
			tree[cur].lazy_filp ^= 1;
			tree[cur].sum = len( left, rig ) - tree[cur].sum;
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		push_down( cur, left, rig );
		if( from <= mid ) 
			flip( from, to, cur << 1, left, mid );
		if( to > mid ) 
			flip( from, to, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void flip( cint from, cint to ) { return flip( from, to, 1, 1, n ); }/*}}}*/

	int query( cint from, cint to, cint cur, cint left, cint rig ) {/*{{{*/
		if( from <= left && rig <= to ) { return tree[cur].sum; }

		cint mid = ( left + rig ) >> 1;
		int res = 0;
		push_down( cur, left, rig );
		if( from <= mid ) 
			res += query( from, to, cur << 1, left, mid );
		if( to > mid ) 
			res += query( from, to, cur << 1 | 1, mid + 1, rig );

		push_up(cur);

		return res;
	}
	int query( cint from, cint to ) { return query( from, to, 1, 1, n ); }
} sgt;

int main() {
#ifdef woshiluo
	freopen( "tmp.in", "r", stdin );
	freopen( "tmp.out", "w", stdout );
#else
	freopen( "chtholly.in", "r", stdin );
	freopen( "chtholly.out", "w", stdout );
#endif
	cint n = read<int>();
	sgt.n = n;
	cint m = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		cint op = read<int>();
		cint x = read<int>();
		cint y = read<int>();
		if( op == 0 ) 
			sgt.set( x, y, 0 );
		if( op == 1 ) 
			sgt.set( x, y, 1 );
		if( op == 2 ) 
			sgt.flip( x, y );;
		if( op == 3 ) 
			printf( "%d\n", sgt.query( x, y ) );
		
	}
	
}
