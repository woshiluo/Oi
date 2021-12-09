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

int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }

int main() {
	int T = read<int>();
	while( T -- ) {
		static int bit[40];
		memset( bit, 0, sizeof(bit) );
		int n = read<int>(), _gcd = 0;
		for( int i = 1; i <= n; i ++ ) {
			int tmp = read<int>();
			for( int j = 0; j < 30; j ++ ) {
				bit[j] += ( ( tmp >> j ) & 1 );
				_gcd = bit[j];
			}
		}
		for( int j = 0; j < 30; j ++ ) {
			if( bit[j] ) 
				_gcd = gcd( bit[j], _gcd );
		}
		for( int i = 1; i <= _gcd; i ++ ) {
			if( _gcd % i == 0 ) 
				printf( "%d ", i );
		}
		if( _gcd == 0 ) {
			for( int i = 1; i <= n; i ++ ) {
				printf( "%d ", i );
			}
		}
		printf( "\n" );
	}
}
