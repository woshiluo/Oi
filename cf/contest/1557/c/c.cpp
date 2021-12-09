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
T pow( T a, ll p ) {
	T res = 1;
	while( p ) {
		if( p & 1LL ) 
			res = res * a;
		a = a * a;
		p >>= 1LL;
	}
	return res;
}/*}}}*/

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

const int N = 2e5 + 1e4;

ModInt fac[N], rfac[N];

void init_fac( int n ) {
	fac[0] = 1;
	for( int i = 1; i <= n; i ++ ) 
		fac[i] = fac[ i - 1 ] * i;
	rfac[n] = (ModInt)1 / fac[n];
	for( int i = n - 1; i >= 0; i -- ) 
		rfac[i] = rfac[ i + 1 ] * ( i + 1 );
}

// choose n in m
ModInt choose( int n, int m ) {
	return fac[m] * rfac[n] * rfac[ m - n ];
}

void work() {
	int n, k;
	n = read<int>(); k = read<int>();
	if( n == 1 ) {
		pow( (ModInt)2, k ).output();
		return ;
	}
	init_fac(n);
	ModInt base2 = 0;
	for( int i = 0; i < n; i += 2 ) 
		base2 += choose( i, n );
	ModInt res = pow( base2 + ( n & 1 ), k );
	// get_full
	for( int i = 1; i <= k; i ++ ) {
		if( n % 2 == 0 )
			res += pow( base2, i - 1 ) * pow( (ModInt)2, 1LL * ( k - i ) * n );
	}
	res.output();
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		work();
	}
}
