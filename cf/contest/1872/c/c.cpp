/*
 * c.cpp 2023-09-07
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

#include <vector>
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

void check_prime( cint cur ) {
	for( int i = 2; 1LL * i * i <= cur; i ++ ) {
		if( cur % i == 0 ) {
			printf( "%d %d\n", cur / i, ( cur / i ) * ( i - 1 ) );
			return ;
		}
	}
	printf( "-1\n" );
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		int l = read<int>();
		cint r = read<int>();
		if( l <= 2 ) 
			l = 3;
		if( r < l ) {
			printf( "-1\n" );
			continue;
		}

		if( l == r ) {
			check_prime(l);
		}
		else {
			if( l & 1 ) 
				printf( "%d %d\n", ( l + 1 ) >> 1, ( l + 1 ) >> 1 );
			else 
				printf( "%d %d\n", ( l ) >> 1, ( l ) >> 1 );
		}
	}
}
