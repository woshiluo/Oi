/*
 * a.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

const int N = 3100;
const int mod = 1e9 + 7;

template <class T>/*{{{*/
inline T Min( T a, T b ) { return a < b? a: b; }
template <class T>
inline T Max( T a, T b ) { return a > b? a: b; }
template <class T>
inline void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template <class T>
inline void chk_Max( T &a, T b ) { if( a < b ) a = b; }

inline int full_pow( int k ) { return 1 << k; }
inline bool has( int cur, int k ) { return cur & ( 1 << k ); }

inline bool is_digit( char cur ) { return cur >= '0' && cur <= '9'; }
template <class T>
T read() {
	T res = 0, k = 1; char x = getchar();
	for( ; !is_digit(x); x = getchar() )
		if( x == '-' ) 
			k = -1;
	for( ; is_digit(x); x = getchar() ) 
		res = res * 10 + ( x - '0' );
	return res * k;
}

template <class T>
T pow( T a, int p ) {
	T res = 1; 
	while(p) {
		if( p & 1 ) 
			res *= a;
		a *= a;
		p >>= 1;
	}
	return res;
}
/*}}}*/

struct ModInt {
	int cur; 
	ModInt( int val = 0 ) { cur = ( ( val % mod ) + mod ) % mod; }

	ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	void operator += ( const ModInt &b ) { *this = (*this) + b; }
	void operator -= ( const ModInt &b ) { *this = (*this) - b; }
	void operator *= ( const ModInt &b ) { *this = (*this) * b; }
	void operator /= ( const ModInt &b ) { *this = (*this) / b; }

	inline void output( const char end = '\n' ) const { printf( "%d%c", cur, end ); }
};

ModInt fact( int cur ) {
	ModInt res = 1;
	for( int i = 1; i <= cur; i ++ ) 
		res *= i;
	return res;
}

ModInt f[N][N];
int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int T = read<int>();
	const ModInt mod2 = (ModInt)2;
	f[0][0] = 1;
	for( int i = 1; i < N; i ++ ) {
		for( int j = 0; j < N; j ++ ) {
			if( j == 0 ) 
				f[i][j] = f[ i - 1 ][j];
			else
				f[i][j] = f[ i - 1 ][ j - 1 ] * ( ( pow( mod2, n ) - 1 ) - ( pow( mod2, j - 1 ) - 1 ) ) +
					f[ i - 1 ][j] * pow( mod2, j );
		}
	}
	while( T -- ) {
		ModInt res = 1, ans = 0;
		int n, m;
		n = read<int>(); m = read<int>();
		f[n][m].output();
	}
}
