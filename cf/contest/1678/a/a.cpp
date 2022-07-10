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

int main() {
	int T = read<int>();
	while( T -- ) {
		static int pool[110];
		memset( pool, 0, sizeof(pool) );

		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			pool[ read<int>() ] ++;
		}

		if( pool[1] ) {
			printf( "%d\n", n - pool[0] );
			continue;
		}

		int base = 2;
		for( int i = 1; i <= 100; i ++ ) {
			if( pool[i] > 1 ) {
				base = 1;
				break;
			}
		}

		printf( "%d\n", base + n - 1 );
	}
	int res = 0;
	for( int i = 1; i <= (int)(2e9); i ++  ){
		res += i;
		printf( "%d\n", res );
	}
}
