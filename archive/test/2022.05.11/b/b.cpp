/*
 * b.cpp
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
		int n = read<int>();
		int cnt_1 = 0, cnt_2 = 0, sum = 0;
		for( int i = 1; i <= n; i ++ ) {
			int tmp = read<int>();
			if( tmp == 1 ) 
				cnt_1 ++;
			if( tmp == 2 ) 
				cnt_2 ++;
			sum += tmp;
		}

		if( cnt_1 == n ) {
			printf( "%s\n", ( n % 3 )? "YES": "NO" );
		}
		else {
			if( cnt_1 == n - 1 && cnt_2 == 1 ) 
				printf( "%s\n", ( n % 3 == 1 )? "NO": "YES" );
			else {
				if( cnt_1 & 1 ) 
					printf( "YES\n" );
				else
					printf( "%s\n", ( n + sum ) % 2 ? "NO": "YES" );
			}
		}
	}
}
