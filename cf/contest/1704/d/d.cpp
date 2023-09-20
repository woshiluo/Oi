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

template <class T>
T aabs( T cur ) { return cur < 0? -cur: cur; }

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint m = read<int>();
		cint n = read<int>();

		std::vector<std::vector<ll>> c( m + 1 );
		for( int i = 1; i <= m; i ++ ) {
			c[i].resize( n + 1 );
			for( int j = 1; j <= n; j ++ ) {
				c[i][j] = read<int>();
				c[i][j] += c[i][ j - 1 ];
			}
		}

		{
			ll r1 = 0, r2 = 0;
			for( int j = 1; j <= n; j ++ ) {
				r1 += c[1][j] - c[2][j];
				r2 += c[1][j] - c[3][j];
			}
			if( r1 != 0 && r2 != 0 ) {
				printf( "%d %lld\n", 1, aabs(r1) );
				continue;
			}
		}

		for( int i = 2; i <= m; i ++ ) {
			ll res = 0;
			for( int j = 1; j <= n; j ++ ) {
				res += c[i][j] - c[ i - 1 ][j];
			}
			if( res != 0 ) {
				printf( "%d %lld\n", i, aabs(res) );
				break;
			}
		}
	}
}
