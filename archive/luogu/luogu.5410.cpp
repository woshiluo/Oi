/*
 * luogu.5410.cpp
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

const int N = 2e7 + 5;

char a[N], b[N];
int z[N], p[N];

int main() {
#ifdef woshiluo
	freopen( "luogu.5410.in", "r", stdin );
	freopen( "luogu.5410.out", "w", stdout );
#endif
	scanf( "%s", b + 1 );
	scanf( "%s", a + 1 );

	int len_a = strlen( a + 1 );
	int len_b = strlen( b + 1 );
	ll res_z = 0, res_p = 0;

	for( int i = 1, l = 0, r = 0; i <= len_a; i ++ ) {
		if( r >= i ) 
			z[i] = Min( z[ i - l + 1 ], r - i + 1 );
		while( i + z[i] <= len_a && a[ z[i] + 1 ] == a[ i + z[i] ] ) 
			z[i] ++;
		if( i != 1 && i + z[i] - 1 >= r ) {
			l = i;
			r = i + z[i] - 1;
		}

		res_z ^= 1LL * i * ( z[i] + 1 );
	}

	for( int i = 1, l = 0, r = 0; i <= len_b; i ++ ) {
		if( r >= i )
			p[i] = Min( z[ i - l + 1 ], r - i + 1 );
		while( i + p[i] <= len_b && a[ p[i] + 1 ] == b[ i + p[i] ] ) 
			p[i] ++;
		if( i != 1 && i + p[i] - 1 >= r ) {
			l = i;
			r = i + p[i] - 1;
		}

		res_p ^= 1LL * i * ( p[i] + 1 );
	}

	printf( "%lld\n%lld\n", res_z, res_p );
} 
