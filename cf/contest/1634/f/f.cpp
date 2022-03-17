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

#include <random>
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

const int N = 3e5 + 1e4;
int mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( ll _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

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

ModInt a[N], b[N], c[N], d[N], f[N];

struct SegmentTree {
	struct Node {
		ModInt val;
		bool all_zero;

		void update() {
			all_zero = ( val.cur == 0 );
		}
	} tree[ N << 2 ];
	int n;

	void push_up( int cur ) {
		tree[cur].val = 1;
		tree[cur].all_zero = ( tree[ cur << 1 ].all_zero && tree[ cur << 1 | 1 ].all_zero );
	}

	void build( int cur, int left, int rig, ModInt val[] ) {
		tree[cur].val = 1; tree[cur].all_zero = false;
		if( left == rig ) {
			tree[cur].val = val[left];
			tree[cur].update();
			return ;
		}

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid, val );
		build( cur << 1 | 1, mid + 1, rig, val );

		push_up(cur);
	}
	void init( int _n, ModInt val[] ) { n = _n; build( 1, 1, n, val ); }

	void add( int pos, ModInt val, int cur, int left, int rig ) {
		if( left == rig && left == pos ) {
			tree[cur].val += val;
			tree[cur].update();
			return ;
		}

		int mid = ( left + rig ) >> 1;
		if( pos <= mid )
			add( pos, val, cur << 1, left, mid );
		else
			add( pos, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void add( int pos, ModInt val ) { add( pos, val, 1, 1, n ); }

	bool all_zero() { return tree[1].all_zero; }
};

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	int n = read<int>(); int q = read<int>(); mod = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		b[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		c[i] = a[i] - b[i];
	}
	d[1] = c[1]; d[2] = c[2] - c[1];
	for( int i = 3; i <= n; i ++ ) {
		d[i] = c[i] - c[ i - 1 ] - c[ i - 2 ];
	}
	f[1] = f[2] = 1;
	for( int i = 3; i <= n + 10; i ++  )
		f[i] = f[ i - 1 ] + f[ i - 2 ];

	SegmentTree sgt; sgt.init( n, d );
	while( q -- ) {
		char op[3]; int x, y;
		scanf( "%s", op ); 
		x = read<int>(); y = read<int>();

		int k = ( op[0] == 'A' )? 1: -1; 
		auto len = [] ( const int _left, const int _rig ) { return _rig - _left + 1; };
		sgt.add( x, (ModInt) 1 * k );
		if( y + 1 <= n )
			sgt.add( y + 1, f[ len( x, y ) + 1 ] * k * -1 );
		if( y + 2 <= n )
			sgt.add( y + 2, f[ len( x, y ) ] * k * -1 );

		printf( "%s\n", sgt.all_zero()? "YES": "NO" );
	}
}
