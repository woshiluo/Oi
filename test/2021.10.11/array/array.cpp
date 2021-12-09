/*
 * array.cpp
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

const int N = 262144;

int f[N][70];

int main() {
	freopen( "array.in", "r", stdin );
	freopen( "array.out", "w", stdout );

	int n = read<int>();
	int res = 0;
	for( int i = 1; i <= n; i ++ ) {
		int tmp = read<int>();
		f[i][tmp] = i;
	}
	for( int j = 2; j <= 64; j ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			if( f[i][ j - 1 ]  )
				f[i][j] = f[ f[i][ j - 1 ] + 1 ][ j - 1 ];
			if( f[i][j] ) 
				chk_Max( res, j );
		}
	}

	printf( "%d\n", res );
}
