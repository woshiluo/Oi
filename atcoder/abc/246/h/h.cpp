/*
 * h.cpp
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

const int N = 1e5 + 1e4;
const int mod = 998244353;

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

struct Matrix {/*{{{*/
	const static int K = 3;
	ModInt a[K][K];
	Matrix( const int val = 1 ) {
		memset( a, 0, sizeof(a) );
		if( val != 0 )
			for( int i = 0; i < K; i ++ ) 
				a[i][i] = val;
	}

	Matrix operator* ( const Matrix &_b ) const {
		Matrix res(0);
		for( int i = 0; i < K; i ++ ) {
			for( int j = 0; j < K; j ++ ) {
				for( int k = 0; k < K; k ++ ) {
					res.a[i][j] += a[i][k] * _b.a[k][j];
				}
			}
		}
		return res;
	}
	void operator*= ( const Matrix &_b ) { (*this) = (*this) * _b; }

	ModInt* operator[] ( const int pos ) { return a[pos]; }
};/*}}}*/

struct SegmentTree {
	int n;
	Matrix tree[ N << 2 ];

	inline void push_up( const int cur ) { tree[cur] = tree[ cur << 1 ] * tree[ cur << 1 | 1 ]; }

	void build( int cur, int left, int rig ) {
		tree[cur] = 1;
		if( left == rig ) {
			return ;
		}

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		
		push_up(cur);
	}
	void init( const int _n ) { n = _n; build( 1, 1, n ); }

	void set( int pos, Matrix val, int cur, int left, int rig ) {
		if( left == rig && pos == left ) {
			tree[cur] = val;
			return ;
		}

		int mid = ( left + rig ) >> 1;

		if( pos <= mid )
			set( pos, val, cur << 1, left, mid );
		else 
			set( pos, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void set( int pos, Matrix val ) { set( pos, val, 1, 1, n ); }

	Matrix query( int from, int to, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) 
			return tree[cur];

		int mid = ( left + rig ) >> 1;
		Matrix res;

		if( from <= mid ) 
			res *= query( from, to, cur, left, mid );
		if( to > mid ) 
			res *= query( from, to, cur, mid + 1, rig );

		return res;
	}
	Matrix query( int from, int to ) { return query( from, to, 1, 1, n ); }
} sgt;

int main() {
#ifdef woshiluo
	freopen( "h.in", "r", stdin );
	freopen( "h.out", "w", stdout );
#endif
	// 2 ?
	Matrix p0, p1, p2, base(0);
	p0[0][0] = 1; p0[1][0] = 1; p0[2][0] = 1;
	p0[0][1] = 0; p0[1][1] = 1; p0[2][1] = 0;
	p0[0][2] = 0; p0[1][2] = 0; p0[2][2] = 1;

	p1[0][0] = 1; p1[1][0] = 0; p1[2][0] = 0;
	p1[0][1] = 1; p1[1][1] = 1; p1[2][1] = 1;
	p1[0][2] = 0; p1[1][2] = 0; p1[2][2] = 1;

	p2[0][0] = 1; p2[1][0] = 1; p2[2][0] = 1;
	p2[0][1] = 1; p2[1][1] = 1; p2[2][1] = 1;
	p2[0][2] = 0; p2[1][2] = 0; p2[2][2] = 1;

	base[0][2] = 1;

	const int n = read<int>();
	const int q = read<int>();
	sgt.init(n);

	static char str[N];
	scanf( "%s", str + 1 );
	for( int i = 1; i <= n; i ++ ) {
		if( str[i] == '0' )
			sgt.set( i, p0 );
		else if( str[i] == '1' )
			sgt.set( i, p1 );
		else
			sgt.set( i, p2 );
	}

	for( int i = 1; i <= q; i ++ ) {
		int pos; static char op[3];
		scanf( "%d%s", &pos, op );
		if( op[0] == '0' ) 
			sgt.set( pos, p0 );
		else if( op[0] == '1' )
			sgt.set( pos, p1 );
		else
			sgt.set( pos, p2 );

		Matrix res = base * sgt.query( 1, n );
		( res[0][0] + res[0][1] ).output();
	}
}
