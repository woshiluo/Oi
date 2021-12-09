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
template <class T> 
T aabs( T a ) { return a < 0? -a: a; }
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

int a[N], b[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
		}
		int p1 = 0, p2 = 0;
		if( n & 1 ) {
			if( a[1] + a[2] == 0 ) {
				for( int i = 3; i <= n; i ++ ) {
					if( a[1] + a[i] != 0 ) {
						p1 = 2, p2 = i;
						std::swap( a[2], a[i] );
						break;
					}
					if( a[2] + a[i] != 0 ) {
						p1 = 1, p2 = i;
						std::swap( a[1], a[i] );
						break;
					}
				}
			}
			b[1] = b[2] = -a[3];
			b[3] = a[1] + a[2];
			for( int i = 4; i <= n; i += 2 ) {
				b[i] = -a[ i + 1 ];
				b[ i + 1 ] = a[i];
			}
		}
		else {
			for( int i = 1; i <= n; i += 2 ) {
				b[i] = -a[ i + 1 ];
				b[ i + 1 ] = a[i];
			}
		}

		for( int i = 1; i <= n; i ++ ) {
			if( i == p1 ) 
				printf( "%d ", b[p2] );
			else if( i == p2 ) 
				printf( "%d ", b[p1] );
			else
				printf( "%d ", b[i] );
		}
		printf( "\n" );
	}
}
