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

const int N = 110;

int a[N], b[N];
ll f[N][2];

int aabs( int cur ) { return cur < 0? -cur: cur; }

ll calc( int pos, bool s1, bool s2 ) {
	int a1 = a[pos], b1 = b[pos];
	int a2 = a[pos + 1], b2 = b[pos + 1];
	if( s1 )
		std::swap( a1, b1 );
	if( s2 ) 
		std::swap( a2, b2 );
	return aabs( a1 - a2 ) + aabs( b1 - b2 );
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		const int n = read<int>();
		for( int i = 1; i <= n; i ++ ) 
			a[i] = read<int>();
		for( int i = 1; i <= n; i ++ ) 
			b[i] = read<int>();

		f[1][0] = f[1][1] = 0;
		for( int i = 2; i <= n; i ++ ) {
			f[i][0] = Min( f[ i - 1 ][1] + calc( i - 1, 1, 0 ), f[ i - 1 ][0] + calc( i - 1, 0, 0 ) );
			f[i][1] = Min( f[ i - 1 ][1] + calc( i - 1, 1, 1 ), f[ i - 1 ][0] + calc( i - 1, 0, 1 ) );
		}
		printf( "%lld\n", Min( f[n][0], f[n][1] ) );
	}
}
