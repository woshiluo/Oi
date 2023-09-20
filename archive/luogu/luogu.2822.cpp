/*
 * luogu.2822.cpp 2023-08-13
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

#include <map>
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

const int N = 2100;

int choose[N][N], sum[N][N];

int main() {
#ifdef woshiluo
	freopen( "luogu.2822.in", "r", stdin );
	freopen( "luogu.2822.out", "w", stdout );
#endif

	cint T = read<int>();
	cint k = read<int>();

	for( int i = 1; i < N; i ++ ) {
		for( int j = 0 ; j <= i; j ++ ) {
			if( j == 0 || j == i ) 
				choose[i][j] = 1;
			else
				choose[i][j] = ( choose[ i - 1 ][j] + choose[ i - 1 ][ j - 1 ] ) % k;

			sum[i][j] = sum[i][ j - 1 ] + ( choose[i][j] == 0 );
		}
	}


	for( int _ = 1; _ <= T; _ ++ ) {
		cint n = read<int>();
		cint m = read<int>();

		int res = 0;
		for( int i = 1; i <= n; i ++ ) {
			res += sum[i][ Min( i, m ) ];
		}
		printf( "%d\n", res );
	}
	
}
