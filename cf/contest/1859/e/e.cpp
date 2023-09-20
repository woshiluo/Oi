/*
 * e.cpp 2023-08-21
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <deque>
#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

const int INF = 0x3f3f3f3f;
const ll LLF = 0x3f3f3f3f3f3f3f3f;

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

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	int T = read<int>();

	while( T -- ) {
		cint n = read<int>();
		cint k = read<int>();

		std::vector<int> a( n + 1 ), b( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
		}
		for( int i = 1; i <= n; i ++ ) {
			b[i] = read<int>();
		}

		std::vector<std::vector<ll>> f(n + 1, std::vector<ll>(n + 1));
		std::deque<ll> p1( n + 1, -LLF ), p2( n + 1, -LLF ), p3( n + 1, -LLF ), p4( n + 1, -LLF );
		// 1  +a + b
		// 2  -a -b
		// 3  +a -b
		// 4  -a +b

		for( int i = 0; i <= n; i ++ ) {
			for( int j = 0; j <= Min ( i, k ); j ++ ) {
				const int diff = i - j;
				if( i - 1 >= 0 ) {
					chk_Max( f[i][j], f[ i - 1 ][j] );
					chk_Max( f[i][j], p1[diff] - a[i] - b[i] );
					chk_Max( f[i][j], p2[diff] + a[i] + b[i] );
					chk_Max( f[i][j], p3[diff] + a[i] - b[i] );
					chk_Max( f[i][j], p4[diff] - a[i] + b[i] );
				}
				if( i != n ) {
					chk_Max( p1[diff], f[i][j] + a[ i + 1 ] + b[ i + 1 ] );
					chk_Max( p2[diff], f[i][j] - a[ i + 1 ] - b[ i + 1 ] );
					chk_Max( p3[diff], f[i][j] + a[ i + 1 ] - b[ i + 1 ] );
					chk_Max( p4[diff], f[i][j] - a[ i + 1 ] + b[ i + 1 ] );
				}
			}
		}

		printf( "%lld\n", f[n][k] );
	}
}
