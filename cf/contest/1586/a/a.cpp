/*
 * a.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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

int a[N];

bool check( int cur ) {
	int sqrt = std::sqrt(cur) + 1;
	for( int i = 2; i <= sqrt; i ++ ) {
		if( cur % i == 0 ) 
			return true;
	}
	return false;
}

void print( int n, int pass ) {
	if( pass == 0 ) {
		printf( "%d\n", n );
		for( int i = 1; i <= n; i ++ ) 
			printf( "%d ", i );
	}
	else {
		printf( "%d\n", n - 1 );
		for( int i = 1; i <= n; i ++ ) 
			if( i != pass )
				printf( "%d ", i );
	}
	printf( "\n" );
}

int main() {
	int T = read<int>();
	while( T -- ) {
		int n = read<int>(), sum = 0;
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>(); 
			sum += a[i];
		}
		if( check(sum) ) {
			print( n, 0 );
		}
		else {
			for( int i = 1; i <= n; i ++ ) {
				if( a[i] & 1 ) {
					print( n, i );
					break;
				}
			}
		}
	}
}
