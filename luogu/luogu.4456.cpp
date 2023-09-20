/*
 * luogu.4456.cpp
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

const int N = 1e7 + 50;

int mod = 1;

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

int n, a, b;

ModInt frac[N], rfrac[N];

ModInt _c( int _m, int _n ) {
	return frac[_m] * rfrac[ _n ] * rfrac[ _m - _n ];
}

ModInt lucas( int _m, int _n ) {
	if( _m < _n ) 
		return 0;
	if( _n < mod )
		return _c( _m, _n );
	return lucas( _m / mod, _n / mod ) * lucas( _m % mod, _n % mod );
}

inline void init() {
	frac[0] = rfrac[0] = 1;
	frac[1] = 1;
	for( int i = 2; i <= n + 10; i ++ ) {
		frac[i] = frac[ i - 1 ] * i;
	}

	rfrac[ n + 10 ] = (ModInt)1 / frac[ n + 10 ];

	for( int i = n + 10 - 1; i >= 1; i -- ) {
		rfrac[i] = rfrac[ i + 1 ] * ( i + 1 );
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.4456.in", "r", stdin );
	freopen( "luogu.4456.out", "w", stdout );
#endif
	n = read<int>(); a = read<int>(); b = read<int>(); mod = read<int>();

	init();

	ModInt ans = 0;
	for( int i = 0; i <= n; i ++ ) {
		ans += lucas( n - i + 1, i ) * pow( (ModInt)n - i, a ) * pow( (ModInt)i, b );
	}

	ans.output();
}
