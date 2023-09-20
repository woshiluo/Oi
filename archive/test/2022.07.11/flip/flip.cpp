/*
 * flip.cpp
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

const int N = 5100;
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

int a[N];
ModInt f[N][N][2];

ModInt choose2( cint cur ) { 
	return (ModInt) { 1LL * cur * ( cur - 1 ) / 2LL }; 
}

int main() {
#ifdef woshiluo
	freopen( "flip.in", "r", stdin );
	freopen( "flip.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();

	int tot = 0;
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		tot += ( a[i] != a[ i - 1 ] );
	}
	tot += ( a[n] != a[ n + 1 ] );

	f[0][tot][1] = 1;
	
	for( int i = 1; i <= m; i ++ ) {
		for( int j = 0; j <= ( n + 1 ); j ++ ) {
			f[i][j][0] += f[ i - 1 ][j][1] * ( m - i );
			f[i][j][1] += f[ i - 1 ][j][0] * ( m - i );
			f[i][j][1] -= f[ i - 1 ][j][0] * choose2( n + 1 );

			f[i][j][1] -= f[ i - 1 ][j][1] * j * ( n + 1 - j );
			if( j + 2 <= n + 1 )
				f[i][j][1] -= f[ i - 1 ][ j + 2 ][1] * choose2( j + 2 );
			if( j - 2 >= 0 ) 
				f[i][j][1] -= f[ i - 1 ][ j - 2 ][1] * choose2( n + 1 - ( j - 2 ) );
		}
	}

	( f[m][0][1] * ( ( m & 1 )? -1: 1 ) ).output();
}
