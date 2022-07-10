/*
 * c.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <map>
#include <vector>
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


int mod = 0;

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
	ModInt a[2][2];

	Matrix( int p = 1 ) {
		memset( a, 0, sizeof(a) );
		if( p != 0 ) 
			for( int i = 0; i < 2; i ++ ) 
				a[i][i] = 1;
	}

	Matrix operator* ( const Matrix &_b ) const {
		Matrix res(0);
		for( int i = 0; i < 2; i ++ ) {
			for( int j = 0; j < 2; j ++ ) {
				for( int k = 0; k < 2; k ++ ) {
					res.a[i][j] += a[i][k] * _b.a[k][j];
				}
			}
		}
		return res;
	}

	void operator*= ( const Matrix &_b ) {
		(*this) = (*this) * _b;
	}
};/*}}}*/

struct Fib {/*{{{*/
	ModInt f[2];

	bool operator< ( const Fib &_b ) const {
		if( f[0].cur == _b.f[0].cur )
			return f[1].cur < _b.f[1].cur;
		return f[0].cur < _b.f[0].cur;
	}
	Fib next( cint x ) {
		Matrix p, base;
		p.a[0][0] = 0;
		p.a[1][0] = 1;
		p.a[0][1] = 1;
		p.a[1][1] = 1;

		base.a[0][0] = f[0];
		base.a[0][1] = f[1];

		base *= pow( p, x );

		return (Fib){ base.a[0][0], base.a[0][1] };
	}
};/*}}}*/

int BLOCK = 1 << 16;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int n, m, k;
	n = read<int>(); m = read<int>(); k = read<int>();

	cint nn = ( 1 << n );
	mod = nn;
	BLOCK = std::sqrt(nn) * 4;

	int cnt = 0;
	bool has_ans = true;

	std::map<Fib, int> mp;
	for( int i = 1; i <= k; i ++ ) {
		cint x = read<int>();
		cint y = read<int>();
		cint z = read<int>();
		Fib cur = { x, y };

		bool flag = false;
		for( int j = 0; j < BLOCK; j ++ ) {
			if( mp.count(cur) ) {
				if( mp[cur] != z ) 
					has_ans = false;
				flag = true;
				break;
			}
			cur = cur.next(1);
		}
		if( flag ) 
			continue;
		cnt ++;

		for( int j = 0; j < BLOCK; j ++ ) {
			mp[cur] = z;
			cur = cur.next( BLOCK / 2 );
		}
	}

	if( !has_ans ) {
		printf( "0\n" );
		return 0;
	}
	mod = 998244353;
	pow( (ModInt)m, ( nn - cnt ) % ( mod - 1 ) ).output();
}
