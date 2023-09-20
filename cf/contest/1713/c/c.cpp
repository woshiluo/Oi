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

const int N = 1e5 + 1e4;


int f[N], la[N];


int get_f( cint cur ) {
	if( cur == -1 ) 
		return 1;
	if( f[cur] ) 
		return f[cur];

	for( int i = 0; ; i ++ ) {
		if( 1LL * i * i - cur > cur ) 
			break;
		if( i * i - cur >= 0 ) {
			cint res = get_f( i * i - cur - 1 );
			if( res == 1 ) {
				f[cur] = 1;
				la[cur] = i;
				return f[cur];
			}
		}
	}
	return f[cur];
}

void get_res( cint cur ) {
	if( cur < 0 ) 
		return ;
	cint p2 = la[cur] * la[cur];
	cint st = p2 - cur;

	get_res( p2 - cur - 1 );

	for( int i = st; i <= cur; i ++ ) 
		printf( "%d ", p2 - i );
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint res = get_f( n - 1 );
		
		if( res == 0 ) {
			printf( "-1\n" );
			continue;
		}

		get_res( n - 1 );

		printf( "\n" );
	}
}
