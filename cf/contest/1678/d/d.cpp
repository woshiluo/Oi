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

const int NM = 1e6 + 1e5;

int a[NM], sum[NM], f[NM];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();
		cint nm = n * m;
		static char str[NM];
		scanf( "%s", str + 1 );
		for( int i = 1; i <= nm; i ++ ) {
			a[i] = ( str[i] - '0' );
			sum[i] = sum[ i - 1 ] + a[i];
		}
		for( int i = 1; i <= m; i ++ ) 
			f[i] = 0;
		for( int i = m; i <= nm; i ++ ) {
			cint l = i - m + 1;
			if( sum[i] - sum[ l - 1 ] == 0 ) 
				f[i] = 1;
			else
				f[i] = 0;
		}
		for( int i = 1; i <= m; i ++ ) {
			for( int j = i + m; j <= nm; j += m ) 
				f[j] += f[ j - m ];
		}
		std::vector<bool> vis(m);

		int res = 0, p = 0;
		for( int i = 1; i <= nm; i ++ ) {
			if( a[i] == 1 ) {
				if( !vis[p] ) {
					vis[p] = true;
					res ++;
				}
			}

			int cur = 0;
			if( i % m != 0 ) {
				cint l = 1;
				cint r = i % m;
				if( sum[r] - sum[ l - 1 ] )
					cur = 1;
			}

			// TODO: check
			printf( "%d ", res + cur + ( ( i / m ) - f[i] ) );

			p ++;
			p %= m;
		}
		printf( "\n" );
	}
}
