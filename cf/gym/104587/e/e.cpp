/*
 * e.cpp 2023-10-03
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
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

const int mod = 37;

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


struct Matrix {
	int n;
	ModInt a[11][11];
	Matrix( int _n = 0 ) {
		memset( a, 0, sizeof(a) );
		n = _n;
	}
	Matrix operator* ( const Matrix &_b ) const {
		Matrix res(n);
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= n; j ++ ) {
				for( int k = 1; k <= n; k ++ ) {
					res.a[i][j] += a[i][k] * _b.a[k][j];
				}
			}
		}
		return res;
	}
};


constexpr int get_map( const char cur ) {
	if( cur >= 'A' && cur <= 'Z' ) 
		return cur - 'A';
	if( cur >= '0' && cur <= '9' )
		return cur - '0' + 26;
	if( cur == ' ' )
		return 36;
	std::exit(-1);
}

constexpr int get_remap( const int cur ) {
	if( cur < 26 ) 
		return cur + 'A';
	if( cur < 36 )
		return ( cur - 26 ) + '0';
	if( cur == 36 ) 
		return ' ';
	std::exit(-1);
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n = read<int>();

	Matrix key(n);
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			key.a[i][j] = read<int>();
		}
	}

	char* str = (char*)malloc( n + 2 );
	while( fgets( str, n + 1, stdin ) != NULL ) {
		if( str[0] == '\r' || str[0] == '\n' ) 
			continue;
		while( str[ strlen(str) - 1 ] == '\n' || str[ strlen(str) - 1 ] == '\r' ) 
			str[ strlen(str) - 1 ] = 0;
		while( strlen(str) < (unsigned int)n ) {
			str[ strlen(str) + 1 ] = 0;
			str[ strlen(str) ] = ' ';
		}

		Matrix p(n);
		for( int i = 0; i < n; i ++ ) {
			p.a[ i + 1 ][1] = get_map( str[i] );
		}
		
		p = key * p;

		for( int i = 0; i < n; i ++ ) {
			printf( "%c", get_remap( p.a[ i + 1 ][1].cur ) );
		}
	}
}
