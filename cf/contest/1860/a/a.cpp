/*
 * a.cpp 2023-08-19
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

#include <map>
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

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	int T = read<int>();

	while( T -- ) {
		static char str[110];
		static char res1[110], res2[110];
		scanf( "%s", str );
		cint len = strlen(str) * 2;

		for( int i = 0; i < len; i += 2 ) {
			res1[i] = '('; res1[ i + 1 ] = ')';
		}
		for( int i = 0; i < ( len >> 1 ); i ++ ) {
			res2[i] = '('; res2[ i + ( len >> 1 ) ] = ')';
		}

		res1[len] = 0;
		res2[len] = 0;

//		printf( "%s\n", res1 );
//		printf( "%s\n", res2 );

		if( strstr( res1, str ) == 0 ) {
			printf( "YES\n" );
			printf( "%s\n", res1 );
			continue; 
		}
		if( strstr( res2, str ) == 0 ) {
			printf( "YES\n" );
			printf( "%s\n", res2 );
			continue;
		}

		printf( "No\n" );
	}

	
}
