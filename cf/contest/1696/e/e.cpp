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

const int N = 4e5 + 1e4;
const int mod = 1e9 + 7;

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

int a[N];
ModInt frac[N], ifra[N];

void pre() {
	frac[0] = 1; ifra[0] = 1;
	for( int i = 1; i < N; i ++ ) 
		frac[i] = frac[ i - 1 ] * i;
	ifra[ N - 1 ] = (ModInt)1 / frac[ N - 1 ];
	for( int i = N - 2; i; i -- ) 
		ifra[i] = ifra[ i + 1 ] * ( i + 1 );
}

ModInt choose( cint n, cint m ) { return frac[n] * ifra[m] * ifra[ n - m ]; }

int main() {
	pre();

	cint n = read<int>();
	for( int i = 0; i <= n; i ++ ) 
		a[i] = read<int>();

	int la = -1;
	ModInt res = 0;
	for( int i = 0; i <= n; i ++ ) {
		if( a[i] > a[ i + 1 ] ) {
			res += choose( i + a[i] + 1, i + 1 ) - 1;
			if( la != -1 ) 
				res -= choose( la + a[i] + 1, la + 1 ) - 1;
			la = i;
		}
	}

	res.output();
}
