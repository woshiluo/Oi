/*
 * c.cpp
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

const int N = 2e5 + 1e4;
const int FULL = ( 1 << 30 ) - 1;
const int mod = 1e9 + 7;

struct ModInt {/*{{{*/
	int cur;
	ModInt( int _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

struct SegmentTree {/*{{{*/
	int n;
	struct Node { int lazy; } tree[ N << 2 ];

	void build( int cur, int left, int rig ) {
		tree[cur].lazy = FULL;
		if( left == rig ) 
			return ;
		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
	}
	void build( int _n ) { n = _n; build( 1, 1, n ); }

	void add( int from, int to, int val, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			tree[cur].lazy &= val;
			return ;
		}
		int mid = ( left + rig ) >> 1;
		if( from <= mid ) 
			add( from, to, val, cur << 1, left, mid );
		if( to > mid )
			add( from, to, val, cur << 1 | 1, mid + 1, rig );
	}
	void add( int from, int to, int val ) { add( from, to, val, 1, 1, n ); }

	int query( int pos, int cur, int left, int rig ) {
		if( left == rig && left == pos ) {
			return tree[cur].lazy;
		}

		int mid = ( left + rig ) >> 1;
		if( pos <= mid ) 
			return tree[cur].lazy & query( pos, cur << 1, left, mid );
		if( pos > mid ) 
			return tree[cur].lazy & query( pos, cur << 1 | 1, mid + 1, rig );

		return 0;
	}
	int query( int pos ) { return query( pos, 1, 1, n ); }
} sgt;/*}}}*/


int a[N], bit[60];
ModInt fac[N], rfac[N];

void init() {
	fac[0] = 1;
	for( int i = 1; i < N; i ++ )
		fac[i] = fac[ i - 1 ] * i;
	rfac[ N - 1 ] = (ModInt)1 / fac[ N - 1 ];
	for( int i = N - 2; i >= 0; i -- ) 
		rfac[i] = rfac[ i + 1 ] * ( i + 1 );
}

// choose n in m
ModInt choose( int n, int m ) { return fac[m] * rfac[n] * rfac[ m - n ]; }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w" ,stdout );
#endif
	init();
	int T = read<int>();
	while( T -- ) {
		int n, m;
		n = read<int>(); m = read<int>();
		sgt.build(n);
		memset( bit, 0, sizeof(bit) );
		for( int i = 1; i <= m; i ++ ) {
			int l, r, x;
			l = read<int>(); r = read<int>(); x = read<int>();
			sgt.add( l, r, x );
		}
		for( int i = 1; i <= n; i ++ ) 
			a[i] = sgt.query(i);
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 0; j < 30; j ++ ) {
				if( a[i] & ( 1 << j ) )
					bit[j] ++;
			}
		}
		ModInt ans = 0;
		for( int k = 0; k < 30; k ++ ) {
			ModInt res = 0;
			for( int i = 1; i <= bit[k]; i += 2 ) 
				res += choose( i, bit[k] );
			ans += res * pow( (ModInt)2, n - bit[k] ) * pow( (ModInt)2, k );
		}
		ans.output();
	}
}
