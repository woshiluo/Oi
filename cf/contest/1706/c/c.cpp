/*
 * c.cpp
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

const int N = 1e5 + 1e4;

int a[N];
int max[N];
ll val[N];

int main() {
#ifdef woshiluo 
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		for( int i = 1; i <= n; i ++ ) 
			a[i] = read<int>();

		int cmax = 0; ll cval = 0;
		for( int i = 2; i < n; i ++ ) {
			if( max[ i - 2 ] > cmax ) {
				cmax = max[ i - 2 ];
				cval = val[ i - 2 ];
			}
			if( max[ i - 2 ] == cmax ) 
				chk_Min( cval, val[ i - 2 ] );

			max[i] = cmax + 1;
			val[i] = cval + 1LL * Max( Max( a[ i - 1 ], a[ i + 1 ] ) - a[i] + 1, 0 );
		}
		if( max[ n - 1 ] > cmax ) {
			cmax = max[ n - 1 ];
			cval = val[ n - 1 ];
		}
		if( max[ n - 1 ] == cmax ) 
			chk_Min( cval, val[ n - 1 ] );

		if( max[ n - 2 ] > cmax ) {
			cmax = max[ n - 2 ];
			cval = val[ n - 2 ];
		}
		if( max[ n - 2 ] == cmax ) 
			chk_Min( cval, val[ n - 2 ] );

		printf( "%lld\n", cval );
	}
}
