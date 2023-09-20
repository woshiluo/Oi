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

const int N = 110;

int a[N], b[N];

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();

		for( int i = 1; i <= n; i ++ ) 
			scanf( "%1d", &a[i] );
		for( int i = 1; i <= m; i ++ ) 
			scanf( "%1d", &b[i] );

		int diff = n - m;
		bool flag = true;
		bool has_0 = false;
		bool has_1 = false;
		for( int i = 2; i <= m; i ++ ) {
			if( a[ i + diff ] != b[i] )
				flag = false;
		}
		for( int i = 1; i <= diff + 1; i ++ ) {
			if( a[i] == 1 ) 
				has_1 = true;
			if( a[i] == 0 ) 
				has_0 = true;
		}

		if( flag ) {
			if( b[1] == 1 && has_1 ) {
				printf( "YES\n");
				continue;
			}
			if( b[1] == 0 && has_0 ) {
				printf( "YES\n");
				continue;
			}
		}
		printf( "NO\n" );
	}
}
