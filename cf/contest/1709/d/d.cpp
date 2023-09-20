/*
 * d.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cmath>
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
const int K = 20;

int a[N], st[N][K];

int get( int l, int r ) {
	if( l > r ) 
		std::swap( l, r );
	cint len = r - l + 1;
	cint k = std::log(len) / std::log(2);
	return Max( st[l][k], st[ r - ( 1 << k ) + 1 ][k] );
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();
	for( int i = 1; i <= m; i ++ ) 
		st[i][0] = read<int>() + 1;
	for( int k = 1; k < K; k ++ ) 
		for( int i = 1; i <= m; i ++ ) 
			if( i + ( 1 << k ) - 1 <= m ) 
				st[i][k] = Max( st[i][ k - 1 ], st[ i + ( 1 << ( k - 1 ) ) ][ k - 1 ] );
	int q = read<int>();
	while( q -- ) {
		cint x1 = read<int>();
		cint y1 = read<int>();
		cint x2 = read<int>();
		cint y2 = read<int>();
		cint k = read<int>();
		if( ( x1 - x2 ) % k != 0 || ( y1 - y2 ) % k != 0 ) {
			printf( "NO\n" );
			continue;
		}
		cint allow_max = get( y1, y2 );
		int max = ( n / k ) * k + ( x1 % k );
		while( max > n ) 
			max -= k;

		if( max < allow_max )
			printf( "NO\n" );
		else
			printf( "YES\n" );
	}
}
