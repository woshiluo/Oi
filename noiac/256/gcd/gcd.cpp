/*
 * gcd.cpp
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
	for (; !isdigit(ch); ch = getchar())
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

const int N = 20;
const int LENA = 510;
const int LEN = 5100;

char a[N][LENA];
char b[LEN];

inline char *gen_a( int m ) {
	int len = 0;
	char *res = new char[LEN];
	for( int i = 1; i <= 10; i ++ ) {
		if( m & ( 1 << ( i - 1 ) ) ) {
			int len_a = strlen( a[i] );
			for( int j = 0; j < len_a; j ++ ) {
				res[len] = a[i][j];
				len ++;
			}
		}
	}
	res[len] = 0;
	return res;
}

inline char* gen_b( int x, int y ) {
	char *res = new char[LEN];
	for( int i = x; i <= y; i ++ ) {
		res[ i - x ] = b[ i - 1 ];
	}
	res[ y - x + 1 ] = 0;
	return res;
}

int lcs( char *str1, char *str2 ) {
	static int f[LEN][LEN];
	memset( f, 0, sizeof(f) );
	int len1 = strlen(str1), len2 = strlen(str2);
	for( int i = 1; i <= len1; i ++ ) {
		for( int j = 1; j <= len2; j ++ ) {
			if( str1[ i - 1 ] == str2[ j - 1 ] ) 
				f[i][j] = f[ i - 1 ][ j - 1 ] + 1;
			else
				f[i][j] = Max( f[ i - 1 ][j], f[i][ j - 1 ] );
		}
	}
	delete []str1; delete []str2;
	return f[len1][len2];
}

int main() {
#ifdef woshiluo
	freopen( "gcd.in", "r", stdin );
	freopen( "gcd.out", "w", stdout );
#endif
	int n, q;
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%s", a[i] );
	}
	scanf( "%s", b );
	scanf( "%d", &q );
	while( q -- ) {
		int m, x, y;
		scanf( "%d%d%d", &m, &x, &y );
		printf( "%d\n", lcs( gen_a(m), gen_b( x, y ) ) );
	}
}
