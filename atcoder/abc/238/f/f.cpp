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

const int N = 510;

int p[N], q[N], v[N];
ModInt f[2][N][N];

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	int n, k;
	n = read<int>(); k = read<int>();

	for( int i = 1; i <= n; i ++ ) {
		p[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		q[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		v[ p[i] ] = q[i];
	}

	int cur = 0, la = 1;
	f[la][0][ n + 1 ] = 1;

	for( int o = 1; o <= n; o ++, cur ^= 1, la ^= 1 ) {
		for( int i = 0; i < N; i ++ ) 
			for( int j = 0; j < N; j ++ )
				f[cur][i][j] = 0;
		for( int i = 0; i <= k; i ++ ) {
			for( int j = 1; j <= n + 1; j ++ ) {
				if( v[o] < j ) {
					f[cur][ i + 1 ][j] += f[la][i][j];
				}
				f[cur][i][ Min( v[o], j ) ] += f[la][i][j];
			}
		}
	}
	ModInt res = 0;
	for( int i = 0; i <= n + 1; i ++ ) 
		res += f[la][k][i];
	res.output();
}
