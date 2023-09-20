/*
 * gcd.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

const int N = 1e5 + 1e4;

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

int n, q;

struct SegmentTree {/*{{{*/
	int tree[ N << 2 ];

	inline void push_up( int cur ) { tree[cur] = Max( tree[ cur << 1 ], tree[ cur << 1 | 1 ] ); }

	void set( int pos, int val, int cur, int left, int rig ) {
		if( left == rig && left == pos ) {
			chk_Max( tree[cur], val );
			return ;
		}

		int mid = ( left + rig ) >> 1;
		if( pos <= mid ) 
			set( pos, val, cur << 1, left, mid );
		if( pos > mid )
			set( pos, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void set( int pos, int val ) { set( pos, val, 1, 1, n ); }

	int query( int from, int to, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) 
			return tree[cur];

		int mid = ( left + rig ) >> 1, res = 0;
		if( from <= mid ) 
			chk_Max( res, query( from, to, cur << 1, left, mid ) );
		if( to > mid ) 
			chk_Max( res, query( from, to, cur << 1 | 1, mid + 1, rig ) );

		return res;
	}
	int query( int from, int to ) { return query( from, to, 1, 1, n ); }
}; /*}}}*/

struct Seq { int id, l, r; };

SegmentTree sgt;
int lst[N], a[N], ans[N];
std::vector<Seq> seq;

void try_add( int cur, int pos ) {
	int sqrt = std::sqrt(cur);
	for( int i = 1; i <= sqrt; i ++ ) {
		if( cur % i == 0 ) {
			if( lst[i] ) 
				sgt.set( lst[i], i );
			if( lst[ cur / i ] ) 
				sgt.set( lst[ cur / i ], cur / i );
			lst[i] = lst[ cur / i ] = pos;
		}
	}
}

int main() {
	freopen( "gcd.in", "r", stdin );
	freopen( "gcd.out", "w", stdout );

	n = read<int>(); q = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	for( int i = 1; i <= q; i ++ ) {
		int l, r;
		l = read<int>(); r = read<int>();
		seq.push_back( (Seq) { i - 1, l, r } );
	}
	std::sort( seq.begin(), seq.end(), []( const Seq &_a, const Seq &_b ) { 
		if( _a.r == _b.r ) return _a.l < _b.l;
		return _a.r < _b.r;
	});

	int p = 1;
	for( int i = 0; i < q; i ++ ) {
		while( p <= seq[i].r ) {
			try_add( a[p], p );
			p ++;
		}
		ans[ seq[i].id ] = sgt.query( seq[i].l, seq[i].r );
	}

	for( int i = 0; i < q; i ++ ) {
		printf( "%d\n", ans[i] );
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
