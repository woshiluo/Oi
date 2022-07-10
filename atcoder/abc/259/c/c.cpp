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

const int N = 2e5 + 1e4;

void no_sol() {
	printf( "No\n" );
	std::exit(0);
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	static char s1[N];
	static char s2[N];

	scanf( "%s", s1 + 1 );
	scanf( "%s", s2 + 1 );

	cint len1 = strlen( s1 + 1 );
	cint len2 = strlen( s2 + 1 );

	int p0 = 1;

	for( int i = 1; i <= len2; i ++ ) {
		if( s1[p0] == s2[i] ) 
			p0 ++;
		else {
			if( p0 <= 2 ) 
				no_sol();
			if( s1[ p0 - 1 ] == s1[ p0 - 2 ] && s1[ p0 - 1 ] == s2[i] ) 
				continue;
			no_sol();
		}
	}

	if( p0 != len1 + 1 )
		no_sol();

	printf( "Yes\n" );
}
