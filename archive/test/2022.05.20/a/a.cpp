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

int a[110][110];
int dx[4] = { +1, 0, -1, 0 };
int dy[4] = { 0, +1, 0, -1 };

int main() {
	int n = read<int>();
	int x = 1, y = 1, cur = 1, p = 0;
	while( cur <= n * n ) {
		a[x][y] = cur;
		x += dx[p];
		y += dy[p];
		if( x > n || y > n || x < 1 || y < 1 || a[x][y] ) {
			x -= dx[p];
			y -= dy[p];
			p ++;
			p %= 4;
			x += dx[p];
			y += dy[p];
		}
		cur ++;
	}
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			printf( "%4d", a[i][j] );
		}
		printf( "\n" );
	}
}
