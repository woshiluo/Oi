/*
 * accelerator.cpp
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

const int N = 1e6 + 20;
const int M = 20;
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

int n, m;
ModInt f[2][M], fac[ N * M ], rfac[ N * M ], ans[N];

// choose m in n
ModInt choose( int _a, int _b ) { 
	if( _a < _b ) 
		return 0;
	return fac[_a] * rfac[_b] * rfac[ _a - _b ]; 
}

void init() {
	int nm = n * m + 10;

	fac[0] = 1;
	for( int i = 1; i <= nm; i ++ ) 
		fac[i] = fac[ i - 1 ] * i;
	rfac[nm] = (ModInt)1 / fac[nm];
	for( int i = nm - 1; i >= 0; i -- ) 
		rfac[i] = rfac[ i + 1 ] * ( i + 1 );
}

void get_ans() {
	int nm = n * m;
	int cur = 0, la = 1;
	for( int i = 0; i < m; i ++ ) 
		f[la][i] = n;
	ModInt inv_m = (ModInt)1 / m;
	for( int i = 1; i <= nm; i ++, cur ^= 1, la ^= 1 ) {
		ModInt sum = choose( nm, i + 1 );
		f[cur][0] = sum;
		for( int j = 0; j < m; j ++ )
			f[cur][0] -= f[la][j] * ( m - j - 1 );
		f[cur][0] *= inv_m;
		for( int j = 1; j < m; j ++ )
			f[cur][j] = f[cur][ j - 1 ] + f[la][ j - 1 ];
		ans[i] = f[cur][0] + choose( nm, i );
	}
}

int main() {
	freopen( "accelerator.in", "r", stdin );
	freopen( "accelerator.out", "w", stdout );

	int q;
	n = read<int>(); m = read<int>(); q = read<int>();
	init();
	get_ans();
	while( q -- ) {
		int x = read<int>();
		ans[x].output();
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
