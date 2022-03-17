/*
 * ex.cpp
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

const int N = 410;
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

int s[N][N];
ModInt f[N][N];

int main() {
	int n, m; 
	n = read<int>(); m = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		int l, r;
		l = read<int>(); r = read<int>();
		s[ l - 1 ][r] ++;
	}
	for( int i = 0; i <= n; i ++ ) {
		for( int j = i + 1; j <= n; j ++ ) {
			s[i][j] += s[i][ j - 1 ];
		}
	}
	for( int j = 0; j <= n; j++ ) {
		for( int i = n - 1; i >= 0; i -- ){
			s[i][j] += s[ i + 1 ][j];
		}
	}

	f[0][0] = 1;
	for( int i = 0; i <= n; i ++ ) {
		for( int j = 0; j <= m; j ++ ) {
			if( f[i][j].cur == 0 ) 
				continue;
			for( int k = i; k <= n; k ++ ) {
				f[ k + 1 ][ j + s[i][k] ] -= f[i][j];
			}
		}
	}

	ModInt ans = 0;
	for( int i = 0; i < m; i ++ ) {
		ans += f[ n + 1 ][i] * m / ( m - i );
	}
	ans.output();
}
