/*
 * e.cpp
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

const int N = 3e6 + 1e5;
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


ModInt fac[N], rfac[N], dp[N][3];

ModInt choose( int n, int m ) {
	if( n < m ) 
		return 0;
	return fac[n] * rfac[m] * rfac[ n - m ];
}
void init( int n ) {
	fac[0] = 1;
	for( int i = 1; i <= n; i ++ ) 
		fac[i] = fac[ i - 1 ] * i;
	rfac[n] = (ModInt)1 / fac[n];
	for( int i = n - 1; i >= 0; i -- ) 
		rfac[i] = rfac[ i + 1 ] * ( i + 1 );
}

void get_dp( int n ) {
	int n3 = 3 * n;
	dp[0][0] = dp[0][1] = dp[0][2] = n;
	ModInt inv_3 = (ModInt)1 / 3;
	for( int i = 1; i <= n3; i ++ ) {
		ModInt sum = choose( n3, i + 1 );
		dp[i][0] = ( sum - dp[ i - 1 ][0] * (ModInt)2 - dp[ i - 1 ][1] ) * inv_3;
		dp[i][1] = dp[i][0] + dp[ i - 1 ][0];
		dp[i][2] = dp[i][1] + dp[ i - 1 ][1];
	}
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n, q;
	n = read<int>(); q = read<int>();
	init( 3 * n ); get_dp(n);
	while( q -- ) {
		int x = read<int>();
		( dp[x][0] + choose( 3 * n, x ) ).output();
	}
}
