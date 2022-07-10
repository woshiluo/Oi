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

int a[N];

int main() {
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		int k = read<int>();
		int cnt = 0;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%1d", &a[i] );
			cnt += a[i];
		}

		if( cnt == 0 ) {
			printf( "0\n" );
			continue;
		}

		int left = 1, rig = n;
		while( a[left] != 1 )
			left ++;
		while( a[rig] != 1 ) 
			rig --;

		rig = ( n - rig ); left = left - 1;

		if( cnt == 1 ) {
			if( k >= rig ) 
				printf( "%d\n", 1 );
			else if( k >= left ) 
				printf( "%d\n", 10 );
			else
				printf( "%d\n", 11 );
			continue;
		}
		else {
			int res = 0;
			if( rig != 0 && k >= rig ) {
				res -= 10;
				k -= rig;
			}
			if( left != 0 && k >= left ) {
				res -= 1;
				k -= left;
			}

			for( int i = 1; i < n; i ++ ) {
				res += ( a[i] * 10 + a[ i + 1 ] );
			}
			printf( "%d\n", res );
		}
	}
}
