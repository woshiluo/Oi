/*
 * e.cpp
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

const int n = 8;

int cx, cy;
// 0 - Done
// 1 - Up
// 2 - Down
int move( int x, int y ) {
	printf( "%d %d\n", x, y );
	cx = x; cy = y;
	fflush(stdout);
	char str[20];
	scanf( "%s", str );
	if( str[0] == 'D' && str[2] == 'n' ) {
		return 0;
	}
	if( str[0] == 'U' && str[1] == 'p' ) {
		return 1;
	}
	if( str[0] == 'D' && str[2] == 'w' ) {
		return 2;
	}
	return 3;
}

bool scanrow( int x ) {
	if( cx != x ) {
		int sta = move( x, cy );
		if( sta == 0 )
			return true;
	}
	for( int i = ( cy == 1? 2: 1 ); i <= n; i ++ ) {
		int sta = move( x, i );
		if( sta == 0 )
			return true;
		if( sta == 1 )
			return scanrow(x);
		if( sta == 2 ) 
			return false;
	}
	return false;
}

void work() {
	int sta = move( 1, 1 );
	if( sta == 0 )
		return ;
	for( int i = 1; i <= n; i ++ ) {
		if( scanrow(i) ) 
			break;
	}
}

int main() {
	int T = read<int>();
	while( T -- ) {
		work();
	}
}
