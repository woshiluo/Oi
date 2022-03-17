/*
 * d.cpp
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

#include <vector>
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

const int N = 1e5 + 1e4;

char str[N][5];
int a[N][5];
bool pool1[30], pool2[30][30], pool3[30][30][30];

bool work() {
	int n = read<int>();
	memset( pool1, 0, sizeof(pool1) );
	memset( pool2, 0, sizeof(pool2) );
	memset( pool3, 0, sizeof(pool3) );
	bool flag = false;
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%s", str[i] );
		int len = strlen( str[i] );
		for( int j = 0; j < len; j ++ ) 
			a[i][j] = ( str[i][j] - 'a' );
		if( len == 1 ) {
			flag = true;
			if( pool1[ a[i][0] ] ) 
				flag = true;
			pool1[ a[i][0] ] = true;
		}
		if( len == 2 ) {
			if( pool2[ a[i][1] ][ a[i][0] ] ) 
				flag = true;
			if( pool1[ a[i][0] ] && pool1[ a[i][1] ] ) 
				flag = true;
			for( int j = 0; j < 26; j ++ ) {
				if( pool3[ a[i][1] ][ a[i][0] ][j] ) 
					flag = true;
				if( pool1[j] ) {
					pool3[j][ a[i][0] ][ a[i][1] ] = true;
				}
			}
			pool2[ a[i][0] ][ a[i][1] ] = true;
		}
		if( len == 3 ) {
			if( pool3[ a[i][2] ][ a[i][1] ][ a[i][0] ] ) 
				flag = true;
			if( pool2[ a[i][2] ][ a[i][1] ] ) 
				flag = true;
			if( pool1[ a[i][0] ] && pool1[ a[i][1] ] && pool1[ a[i][2] ] ) 
				flag = true;
			pool3[ a[i][0] ][ a[i][1] ][ a[i][2] ] = true;
		}
	}
	memset( pool1, 0, sizeof(pool1) );
	memset( pool2, 0, sizeof(pool2) );
	memset( pool3, 0, sizeof(pool3) );
	for( int i = n; i >= 1; i -- ) {
		int len = strlen(str[i]);
		if( len == 1 ) {
			if( pool1[ a[i][0] ] ) 
				flag = true;
			pool1[ a[i][0] ] = true;
		}
		if( len == 2 ) {
			if( a[i][1] == a[i][0] ) 
				flag = true;
			if( pool2[ a[i][1] ][ a[i][0] ] ) 
				flag = true;
			if( pool1[ a[i][0] ] && pool1[ a[i][1] ] ) 
				flag = true;
			for( int j = 0; j < 26; j ++ ) {
				if( pool3[j][ a[i][1] ][ a[i][0] ] ) 
					flag = true;
				if( pool1[j] ) {
					pool3[ a[i][0] ][ a[i][1] ][j] = true;
				}
			}
			pool2[ a[i][0] ][ a[i][1] ] = true;
		}
		if( len == 3 ) {
			if( a[i][0] == a[i][2] ) 
				flag = true;
			if( pool3[ a[i][2] ][ a[i][1] ][ a[i][0] ] ) 
				flag = true;
			if( pool2[ a[i][1] ][ a[i][0] ] ) 
				flag = true;
			if( pool1[ a[i][0] ] && pool1[ a[i][1] ] && pool1[ a[i][2] ] ) 
				flag = true;
			pool3[ a[i][0] ][ a[i][1] ][ a[i][2] ] = true;
		}
	}

	return flag;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		printf( "%s\n", work()? "YES": "NO" );
	} 
}
