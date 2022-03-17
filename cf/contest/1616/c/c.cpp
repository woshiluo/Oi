/*
 * c.cpp
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

int aabs( int a ) { return a < 0? -a: a; }
int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }

int n;
int a[N];

int check( int x, int a1, int a2 ) {
	int y = 0;
	int res = n - 1;
	for( int i = x, cur = a[x]; i <= n; i += a1, cur += a2 ) {
		if( a[i] == cur && i != x && i != y ) 
			res --;
	}
	for( int i = x, cur = a[x]; i >= 1; i -= a1, cur -= a2 ) {
		if( a[i] == cur && i != x && i != y ) 
			res --;
	}
	return res;
}

void calc() {
	n = read<int>();
	for( int i = 1; i <= n; i ++ ) 
		a[i] = read<int>();
	int ans = n - 1;
	for( int i = 1; i <= n; i ++ ) {
		for( int a1 = 1; a1 <= n; a1 ++ ) {
			for( int a2 = -100; a2 <= 100; a2 ++ ) 
				chk_Min( ans, check( i, a1, a2 ) );
		}
	}
	printf( "%d\n", ans );
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		calc();
	}
}
