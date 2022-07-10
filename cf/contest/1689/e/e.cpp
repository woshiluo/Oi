/*
 * e.cpp
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

const int N = 2100;

struct Set {/*{{{*/
	int fa[N];
	void init( cint _n ) { for( int i = 0; i <= _n; i ++ ) fa[i] = i; }
	int get_fa( cint cur ) { 
		if( fa[cur] == cur ) 
			return cur;
		fa[cur] = get_fa(fa[cur]);
		return fa[cur];
	}
	int& operator[] ( cint idx ) { return fa[ get_fa(idx) ]; }
} set;/*}}}*/

int calc( cint n, int a[] ) {
	set.init(n);

	int id = -1;
	for( int i = 1; i <= n; i ++ ) {
		if( a[i] & 1 ) 
			id = i;
	}

	for( int k = 0; k < 30; k ++ ) {
		int la = -1;
		for( int j = 1; j <= n; j ++ ) {
			if( a[j] & ( 1 << k ) ) {
				if( la != -1 ) 
					set[j] = set[la];
				la = j;
			}
		}
	}


	int res = 0;
	for( int i = 1; i <= n; i ++ ) 
		res += ( set[i] == i );

	if( res == 1 ) {
		return 0;
	}

	if( id == -1 ) {
		id = 1;
		a[1] ++;
		res ++;
	}
	for( int i = 1; i <= n; i ++ ) {
		if( set[i] != set[id] ) {
			a[i] ++;
			set[i] = set[id];
		}
	}

	return res - 1;

}
void print( cint n, int a[], int p ) {
	set.init(n);

	int id = -1;
	for( int i = 1; i <= n; i ++ ) 
		if( a[i] & 1 ) 
			id = i;

	for( int i = 1; i <= n; i ++ ) {
		for( int j = i + 1; j <= n; j ++ ) {
			if( a[i] & a[j] ) 
				set[i] = set[j];
		}
	}

	int res = 0;
	for( int i = 1; i <= n; i ++ ) 
		res += ( set[i] == i );

	if( res == 1 ) {
		printf( "%d\n", p );
		for( int i = 1; i <= n; i ++ ) 
			printf( "%d ", a[i] ) ;
		printf( "\n" );
		return ;
	}

	if( id == -1 ) {
		id = 1;
		a[1] ++;
		res ++;
	}
	for( int i = 1; i <= n; i ++ ) {
		if( set[i] != set[id] ) {
			a[i] ++;
			set[i] = set[id];
		}
	}

	printf( "%d\n", res - 1 + p );
	for( int i = 1; i <= n; i ++ ) 
		printf( "%d ", a[i] ) ;
	printf( "\n" );
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		static int a[N], b[N];
		cint n = read<int>();

		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
			b[i] = a[i];
		}

		int id = 0;
		int min = calc( n, b );
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= n; j ++ ) 
				b[j] = a[j];
			if( b[i] == 0 ) 
				continue;
			b[i] --;
			cint res = calc( n, b );
			if( res < min ) {
				min = res;
				id = i;
			}
		}

		for( int j = 1; j <= n; j ++ ) 
			b[j] = a[j];
		b[id] --;
		print( n, b, id != 0 );
	}
}
