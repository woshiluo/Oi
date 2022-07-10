/*
 * a.cpp
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

int main() {
	int T = read<int>();
	while( T -- ) {
		static char str[N];
		static int a[N];
		scanf( "%s", str );
		cint len = strlen(str);
		int tot = 0;
		for( int i = 0; i < len; i ++ ) {
			a[i] = ( str[i] - 'a' + 1 );
			tot += a[i];
		}
		if( len & 1 ) {
			int res = -1;
			if( tot - a[0] > a[0] ) {
				chk_Max( res, tot - a[0] - a[0] );
			}
			cint ed = len - 1;
			if( tot - a[ed] > a[ed] ) {
				chk_Max( res, tot - a[ed] - a[ed] );
			}
			if( res != -1 ) 
				printf( "Alice %d\n", res );
			else
				printf( "Bob %d\n", a[0] );
		}
		else {
			printf( "Alce %d\n", tot );
			continue;
		}
	}
}
