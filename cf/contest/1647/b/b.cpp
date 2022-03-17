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

const int N = 210;

int mp[N][N];

int main() {
	int T = read<int>();
	while( T -- ) {
		int n, m;
		n = read<int>(); m = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				scanf( "%1d", &mp[i][j] );
			}
		}
		bool flag = false;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				if( !mp[i][j] ) {
					if( i - 1 > 0 && j - 1 > 0 ) {
						if( mp[ i - 1 ][ j - 1 ] && mp[ i - 1 ][j] && mp[i][ j - 1 ] ) 
							flag = true;
					}
					if( i - 1 > 0 && j + 1 <= m ) {
						if( mp[ i - 1 ][ j + 1 ] && mp[ i - 1 ][j] && mp[i][ j + 1 ] ) 
							flag = true;
					}
					if( i + 1 <= n && j - 1 > 0 ) {
						if( mp[ i + 1 ][ j - 1 ] && mp[ i + 1 ][j] && mp[i][ j - 1 ] ) 
							flag = true;
					}
					if( i + 1 <= n && j + 1 <= m ) {
						if( mp[ i + 1 ][ j + 1 ] && mp[ i + 1 ][j] && mp[i][ j + 1 ] ) 
							flag = true;
					}
				}
			}
		}
		printf( "%s\n", flag? "NO": "YES" );
	}
}
