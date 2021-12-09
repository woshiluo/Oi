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

const int N = 110;

bool check( char str[] ) {
	int len = strlen(str), a1 = 0, a2 = 0;
	for( int i = 1; i < len; i ++ ) {
		if( str[ i - 1 ] == 'a' && str[i] == 'b' ) 
			a1 ++;
		if( str[ i - 1 ] == 'b' && str[i] == 'a' ) 
			a2 ++;
	}
	return a1 == a2;
}

int main() {
	int T = read<int>();
	while( T -- ) {
		char str[N];
		scanf( "%s", str );
		if( check(str) ) {
			printf( "%s\n", str );
			continue;
		}
		char tmp = str[0];
		str[0] = ( str[0] == 'a'? 'b': 'a' );
		if( check(str) ) {
			printf( "%s\n", str );
			continue;
		}
		str[0] = tmp;
		int len = strlen(str) - 1;
		str[len] = ( str[len] == 'a'? 'b': 'a' );
		if( check(str) ) {
			printf( "%s\n", str );
			continue;
		}
	}
}
