/*
 * stroll.cpp
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

template <class T> 
T aabs( T cur ) { return cur < 0? -cur: cur; }

const int N = 1e6 + 1e5;

ModInt fra[N], ifra[N];

ModInt choose( cint n, cint m ) {
	return fra[n] * ifra[m] * ifra[ n - m ];
}

int main() {
#ifdef woshiluo
	freopen( "stroll.in", "r", stdin );
	freopen( "stroll.out", "w", stdout );
#endif

	cint n = read<int>();
	cint m = read<int>();
	cint _a = read<int>();
	cint _b = read<int>();
	cint _c = read<int>();

	fra[0] = 1;
	for( int i = 1; i <= n; i ++ ) 
		fra[i] = fra[ i - 1 ] * i;

	ifra[n] = (ModInt)1 / fra[n];
	for( int i = n - 1; i >= 0; i -- ) 
		ifra[i] = ifra[ i + 1 ] * ( i + 1 );

	cint a = ( ( ( _b + _c - _a ) % m ) + m ) % m;
	cint b = ( ( ( _a + _c - _b ) % m ) + m ) % m;
	cint c = ( ( ( _a + _b - _c ) % m ) + m ) % m;

	ModInt res[3][2];

	for( int i = 0; i <= n; i ++ ) {
		cint base = n - i - i;
		cint cur = ( ( base % m ) + m ) % m;
		cint k = ( aabs(base) / m ) + ( aabs(base) % m != 0 && base < 0 );
		const ModInt p = choose( n, i );
		if( cur == a ) 
			res[0][ k & 1 ] += p;
		if( cur == b ) 
			res[1][ k & 1 ] += p;
		if( cur == c ) 
			res[2][ k & 1 ] += p;
	}

	if( m & 1 ) {
		( ( res[0][0] + res[0][1] ) * ( res[1][0] + res[1][1] ) * ( res[2][0] + res[2][1] ) ).output();
		return 0;
	}

	ModInt ans = 0;
	for( int i = 0; i < 2; i ++ ) {
		for( int j = 0; j < 2; j ++ ) {
			for( int k = 0; k < 2; k ++ ) {
				cint ta = ( ( b + c + ( j + k ) * m ) / 2 ) % m;
				cint tb = ( ( a + c + ( i + k ) * m ) / 2 ) % m;
				cint tc = ( ( a + b + ( i + j ) * m ) / 2 ) % m;

				if( ta != _a || tb != _b || tc != _c ) 
					continue;
				ans += res[0][i] * res[1][j] * res[2][k];
			}
		}
	}

	ans.output();
}
