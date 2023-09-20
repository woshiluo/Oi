/*
 * 1006.cpp
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

const int N = 1e5 + 1e4;

int a[N];

void add_200( long long &res, long long cur ) {
	if( res < 200000 && res + ( cur * 8 / 10 ) >= 200000 ) {
		const long long t = ( 200000 - res ) * 10 / 8;
		res = 200000; cur -= t;
	}

	if( res >= 200000 ) 
		res += cur * 5 / 10;
	else
		res += cur * 8 / 10;
}

void add_100( long long &res, long long cur ) {
	if( res < 100000 && res + cur >= 100000 ) {
		const long long t = 100000 - res;
		res += t; cur -= t;
	}
	if( res >= 100000 ) 
		add_200( res, cur );
	else
		res += cur;
}

int main() {
#ifdef woshiluo
	freopen( "1006.in", "r", stdin );
	freopen( "1006.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		for( int i = 1; i <= n; i ++ ) 
			a[i] = read<int>();

		ll res1 = 0, res2 = 0;
		for( int i = 1; i <= n; i ++ ) {
			add_100( res1, a[i] * 1000 );
			if( res2 >= 200000 )
				res2 += a[i] * 500;
			else if( res2 >= 100000 ) 
				res2 += a[i] * 800;
			else
				res2 += a[i] * 1000;
		}

		printf( "%.3lf %.3lf\n", 0.001 * res1, 0.001 * res2 );
	}
}
