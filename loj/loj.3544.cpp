/*
 * loj.3544.cpp
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

const int N = 1e6 + 1e5;

bool calc( char res[], int a[], int n, int l1, int r1, int l2, int r2 ) {
	int rig = 2 * ( n - 1 );
	for( int i = 1; i < n; i ++ ) {
		bool allow_1 = ( l1 <= r1 );
		bool allow_2 = ( l2 <= r2 );
		if( allow_1 ) {
			if( l2 <= r2 && a[l1] == a[l2] ) {
				res[i] = 'L';
				res[ rig - i + 1 ] = 'R';
				l1 ++; l2 ++;
				continue;
			}
			else if( l1 < r1 && a[l1] == a[r1] ) {
				res[i] = 'L';
				res[ rig - i + 1 ] = 'L';
				++ l1; -- r1;
				continue;
			}
		}
		if( allow_2 ) {
			if( l2 < r2 && a[l2] == a[r2] ) {
				res[i] = 'R';
				res[ rig - i + 1 ] = 'R';
				++ l2; -- r2;
				continue;
			}
			else if( l1 <= r1 && a[r1] == a[r2] ) {
				res[i] = 'R';
				res[ rig - i + 1 ] = 'L';
				r1 --; r2 --;
				continue;
			}
		}

		return false;
	}
	res[ rig + 1 ] = 0;
	return true;
}

void work() {
	int n; 
	static int a[N];
	static char res[N];

	n = read<int>();
	int n2 = ( n << 1 );
	for( int i = 1; i <= n2; i ++ ) {
		a[i] = read<int>();
	}

	int p1 = 0, p2 = 0;
	for( int i = 1; i <= n2; i ++ ) 
		if( a[i] == a[1] ) 
			p1 = i;
	for( int i = n2; i >= 1; i -- ) 
		if( a[i] == a[n2] ) 
			p2 = i;

	if( calc( res, a, n, 2, p1 - 1, p1 + 1, n2 ) )
		printf( "L%sL\n", res + 1 );
	else if( calc( res, a, n, 1, p2 - 1, p2 + 1, n2 - 1 ) ) 
		printf( "R%sL\n", res + 1 );
	else
		printf( "-1\n" );
}

int main() {
#ifdef woshiluo
	freopen( "loj.3544.in", "r", stdin );
	freopen( "loj.3544.out", "w", stdout );
#else
	freopen( "palin.in", "r", stdin );
	freopen( "palin.out", "w", stdout );
#endif
	int T = read<int>(); 
	while( T -- ) {
		work();
	}
}
