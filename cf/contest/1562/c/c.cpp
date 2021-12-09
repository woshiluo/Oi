/*
 * c.cpp
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

const int N = 2e4 + 1e3;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		int n2 = ( n >> 1 ), cnt_0 = 0;
		char str[N]; int bit[N];
		scanf( "%s", str + 1 );
		for( int i = 1; i <= n; i ++ ) {
			bit[i] = ( str[i] - '0' );
			cnt_0 += ( bit[i] == 0 );
		}
		if( cnt_0 == 0 ) {
			if( n & 1 ) {
				printf( "%d %d %d %d", 1, n2 + 1, n2 + 1, n );
			}
			else 
				printf( "%d %d %d %d", 1, n2, n2 + 1, n );
		}
		else if( ( n & 1 ) && bit[ n2 + 1 ] == 0 && cnt_0 == 1 ) {
			printf( "%d %d %d %d", 1, n, n2 + 1, n );
		}
		else {
			int p1 = 0;
			for( int i = 1; i <= n2; i ++ ) {
				if( !bit[i] ) {
					p1 = i;
					break;
				}
			}
			if( p1 ) {
				printf( "%d %d %d %d", p1, n, p1 + 1, n );
			}
			else {
				for( int i = n; i >= n2 + 1; i -- ) {
					if( !bit[i] ) {
						p1 = i;
						break;
					}
				}
				if( p1 ) {
					printf( "%d %d %d %d", 1, p1, 1, p1 - 1 );
				}
			}
		}
		printf( "\n" );
	}
}
