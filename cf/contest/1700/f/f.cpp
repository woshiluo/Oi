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

int aabs( cint a ) { return a < 0? -a: a; }

const int N = 2e5 + 1e4;

int a[2][N], b[2][N];
int sa[2][N], sb[2][N];

int main() {
	int n = read<int>();
	for( int j = 0; j < 2; j ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			a[j][i] = read<int>();
			sa[j][i] = sa[j][ i - 1 ] + a[j][i];
		}
	}
	for( int j = 0; j < 2; j ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			b[j][i] = read<int>();
			sb[j][i] = sb[j][ i - 1 ] + b[j][i];
		}
	}

	ll res = 0;
	int d1 = 0, d2 = 0;
	for( int i = 1; i <= n; i ++ ) {
		d1 += a[0][i] - b[0][i];
		d2 += a[1][i] - b[1][i];
		if( d1 < 0 && d2 > 0 ) {
			cint t = Min( -d1, d2 );
			d1 += t;
			d2 -= t;
			res += t;
		}
		if( d2 < 0 && d1 > 0 ) {
			cint t = Min( d1, -d2 );
			d1 -= t;
			d2 += t;
			res += t;
		}

		res += aabs( d1 );
		res += aabs( d2 );
	}

	if( sa[0][n] + sa[1][n] != sb[0][n] + sb[1][n] ) 
		printf( "-1\n" );
	else
		printf( "%lld\n", res );
}
