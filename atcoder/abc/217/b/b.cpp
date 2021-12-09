/*
 * b.cpp
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

const int N = 10;

char s1[N], s2[N], s3[N];

int main() {
	scanf( "%s", s1 + 1 );
	scanf( "%s", s2 + 1 );
	scanf( "%s", s3 + 1 );
	if( s1[2] != 'B' && s2[2] != 'B' && s3[2] != 'B' ) 
		printf( "%s\n", "ABC" );
	if( s1[2] != 'R' && s2[2] != 'R' && s3[2] != 'R' ) 
		printf( "%s\n", "ARC" );
	if( s1[2] != 'G' && s2[2] != 'G' && s3[2] != 'G' ) 
		printf( "%s\n", "AGC" );
	if( s1[2] != 'H' && s2[2] != 'H' && s3[2] != 'H' ) 
		printf( "%s\n", "AHC" );
}
