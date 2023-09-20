/*
 * b.cpp
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

const int N = 2100;

ModInt p[N][N], q[N][N];
ModInt f[N][N], g[N][N], ans[N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();
	cint t = Min( read<int>(), n + m - 1 );

	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= t; j ++ ) {
			p[i][j] = p[i][ j - 1 ] * p[ i - 1 ][ j - 1 ];
			if( j <= m )  
				p[i][j] += (ModInt) 1 / m;
			q[i][j] = 1;
			if( j < t ) 
				q[i][j] -= p[ i - 1 ][j];
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j < t; j ++ ) {
			g[i][j] = (ModInt)j * q[i][j] + ( ans[ i - 1 ] - p[ i - 1 ][j] * f[ i - 1 ][j] );
		}
		g[i][t] = (ModInt)t + ans[ i - 1 ];
		for( int j = t; j >= 1; j -- ) {
			f[i][j] = g[i][j] + ( (ModInt)1 - q[i][j] ) * f[i][ j + 1 ];
		}
		for( int j = 1; j <= t; j ++ ) 
			ans[i] += p[i][j] * g[i][j];
	}

	ans[n].output();
}
