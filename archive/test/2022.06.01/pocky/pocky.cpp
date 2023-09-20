/*
 * pocky.cpp
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

const int N = 1100;

ModInt f[2][N][N], g[2][N][N];
bool vis[2][N][N];

int gcd( cint a, cint b ) { return b? gcd( b, a % b ): a; }

int main() {
#ifdef woshiluo
	freopen( "pocky.in", "r", stdin );
	freopen( "pocky.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();

	int cur = 0, la = 1;
	for( int i = 1; i <= n; i ++ ) {
		f[la][i][i] = 0;
		g[la][i][i] = 1;
		vis[la][i][i] = true;
	}
	for( int i = 2; i <= m; i ++, la ^= 1, cur ^= 1 ) {
		for( int j = 1; j <= n; j ++ )
			for( int k = 1; k <= n; k ++ ) {
				f[cur][j][k] = 0;
				g[cur][j][k] = 0;
				vis[cur][j][k] = false;
			}
		for( int j = 1; j <= n; j ++ ) {
			for( int k = 1; k < j; k ++ ) {
				for( int p = 1; p <= j - k; p ++ ) 
					if( vis[la][ j - k ][p] ) {
						f[cur][j][k] += f[la][ j - k ][p] + (ModInt)k * gcd( p, k ) * g[la][ j - k ][p];
						g[cur][j][k] += g[la][ j - k ][p];
						vis[cur][j][k] = true;
					}
			}
		}
	}

	ModInt res = 0;
	for( int i = 1; i <= n; i ++ ) 
		res += f[la][n][i];

	res.output();
}
