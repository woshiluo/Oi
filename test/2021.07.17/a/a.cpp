/*
 * a.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>

template <class T>/*{{{*/
T Max( T a, T b ) { return a > b? a: b; }
inline bool is_digit( const char cur ) { return cur >= '0' && cur <= '9'; }
template <class T>
inline T read() {
	T res = 0, k = 1; char x = getchar();
	for( ; !is_digit(x); x = getchar() ) 
		if( x == '-' ) 
			k = -1;
	for( ; is_digit(x); x = getchar() ) 
		res = res * 10 + ( x - '0' );
	return res * k;
}
template<class T>
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res *= a;
		a *= a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int mod = 998244353;
struct ModInt {/*{{{*/
	int cur;
	ModInt( int val = 0 ) { cur = ( ( val % mod ) + mod ) % mod; }

	ModInt inv() const { return pow( *this, mod - 2 ); }
	ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * b.inv().cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { *this = *this + b; }
	inline void operator-= ( const ModInt &b ) { *this = *this - b; }
	inline void operator*= ( const ModInt &b ) { *this = *this * b; }
	inline void operator/= ( const ModInt &b ) { *this = *this / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

const int N = 5e6 + 1e5;

ModInt fac[N], ifac[N];

inline void init( int n ) {
	fac[0] = 1;
	for( int i = 1; i <= n; i ++ ) {
		fac[i] = fac[ i - 1 ] * i;
	}
	ifac[n] = fac[n].inv();
	for( int i = n - 1; i >= 0; i -- ) {
		ifac[i] = ifac[ i + 1 ] * ( i + 1 );
	}
}

// choose n in m
inline ModInt choose( int n, int m ) {
	if( m < n || n < 0 ) 
		return 0;
	return fac[m] * ifac[n] * ifac[ m - n ];
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int n, a, b;
	n = read<int>(); a = read<int>(); b = read<int>();
	init(n);
	ModInt ans = 0;
	for( int k = Max( a + b - n, 0 ); ( k << 1 ) <= n; k ++ ) {
		if( k & 1 ) 
			ans += ( (ModInt)2 * choose( k / 2, a - k ) * choose( k / 2, b - k ) ) * ( n - ( a + b - k ) + 1 );
		else
			ans += ( choose( k / 2 - 1, a - k - 1 ) * choose( k / 2, b - k + 1 ) +
					choose( k / 2, a - k + 1 ) * choose( k / 2 - 1, b - k - 1 ) ) * 
				( n - ( a + b - k ) + 1 );
	}
	ans.output();
}
