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

int ask_and( int a, int b ) {
	fflush(stdout);
	printf( "and %d %d\n", a, b );
	fflush(stdout);
	int tmp = read<int>();
	return tmp;
}

int ask_or( int a, int b ) {
	fflush(stdout);
	printf( "or %d %d\n", a, b );
	fflush(stdout);
	int tmp = read<int>();
	return tmp;
}

int get_sum( int a, int b ) {
	return ask_and( a, b ) + ask_or( a, b );
}

const int N = 1e4 + 1e3;

int sum[N], a[N];

int main() {
	int n = read<int>(); int k = read<int>();

	for( int i = 2; i <= n; i ++ ) {
		sum[i] = get_sum( 1, i );
	}

	a[1] = ( sum[2] + sum[3] - get_sum( 2, 3 ) ) / 2;
	for( int i = 2; i <= n; i ++ ) 
		a[i] = sum[i] - a[1];

	std::sort( a + 1, a + n + 1 );
	
	printf( "finish %d\n", a[k] );
}
