/*
 * b2.cpp
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

const int N = 2e5 + 1e4;

int a[N], f[N][2];

int main() {
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) 
			scanf( "%1d", &a[i] );
		{
			cint tsum = a[1] + a[2];
			f[2][0] = tsum;
			f[2][1] = 2 - tsum;
		}
		for( int i = 4; i <= n; i += 2 ) {
			cint tsum = a[ i - 1 ] + a[i];
			f[i][0] = Min( f[ i - 2 ][0], f[ i - 2 ][1] ) + tsum;
			f[i][1] = Min( f[ i - 2 ][0], f[ i - 2 ][1] ) + 2 - tsum;
		}
		printf( "%d\n", Min( f[n][0], f[n][1] ) );
	}
}
