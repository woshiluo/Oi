/*
 * d.cpp
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

const int N = 210;

int n;
int a[N], b[N];

int query() {
	printf( "? " );
	for( int i = 1; i <= n; i ++ ) 
		printf( "%d ", a[i] );
	printf( "\n" );
	fflush(stdout);
	int res = read<int>();
	return res;
}

int main() {
	n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = n;
	}
	a[n] = 1;
	int pn = 0;
	for( int i = 1; i < n; i ++ ) {
		for( int j = 1; j < n; j ++ ) {
			a[j] = n - i + 1;
		}
		int k = query();
		if( k != 0 ) {
			pn = n - i + 1;
			break;
		}
	}
	if( pn == 0 ) 
		pn = 1;
	b[n] = pn;
	for( int i = 1; i < n; i ++ ) 
		a[i] = b[n];
	for( int i = 1; i <= n; i ++ ) {
		if( i == pn ) 
			continue;
		a[n] = i;
		int k = query();
		b[k] = i;
	}
	printf( "! " );
	for( int i = 1; i <= n; i ++ ) 
		printf( "%d ", b[i] );
}
