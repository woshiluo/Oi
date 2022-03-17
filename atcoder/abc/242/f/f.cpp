/*
 * f.cpp
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

const int N = 3100;
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

ModInt choose[N][N], f[N][N][2];

void init() {
	choose[0][0] = 1;
	for( int i = 1; i < N; i ++ ) {
		for( int j = 0; j <= i; j ++ ) {
			if( j == 0 || j == i ) 
				choose[i][j] = 1;
			else
				choose[i][j] = choose[ i - 1 ][j] + choose[ i - 1 ][ j - 1 ];
		}
	}
}

ModInt get_f( const int n, const int m, const int x ) {
	ModInt res = 0;
	for( int i = 0; i <= n; i ++ ) {
		for( int j = 0; j <= m; j ++ ) {
			ModInt p = ( ( i + j ) & 1 )? -1: 1;
			res += p * choose[n][i] * choose[m][j] * choose[ ( n - i ) * ( m - j ) ][x];
		}
	}
	return res;
}

int main() {
	int n, m, b, w;
	n = read<int>(); m = read<int>(); b = read<int>(); w = read<int>();
	init();
	for( int k = 0; k < 2; k ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				f[i][j][k] = get_f( i, j, k == 0? w: b );
			}
		}
	}

	ModInt ans = 0;
	for( int x1 = 1; x1 <= n; x1 ++ ) {
		for( int x2 = 1; x2 <= n - x1; x2 ++ ) {
			for( int y1 = 1; y1 <= m; y1 ++ ) {
				for( int y2 = 1; y2 <= m - y1; y2 ++ ) {
					ans += choose[n][x1] * choose[ n - x1 ][x2] * choose[m][y1] * choose[ m - y1 ][y2] * f[x1][y1][0] * f[x2][y2][1];
				}
			}
		}
	}
	ans.output();
}
