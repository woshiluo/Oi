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

#include <cmath>
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

const int N = 2e6 + 1e4;;

ll cost[N], f[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	const int n = read<int>();
	const int C = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		const int x = read<int>();
		const int d = read<int>();
		const int h = read<int>();
		chk_Max( cost[x], 1LL * d * h );
	}
	for( int i = 1; i <= C; i ++ ) {
		for( int j = 1; j * i <= C; j ++ ) {
			chk_Max( f[ i * j ], cost[i] * j );
		}
	}
	for( int i = 1; i <= C; i ++ ) 
		chk_Max( f[i], f[ i - 1 ] );
	int q = read<int>();
	while( q -- ) {
		const ll d = read<ll>();
		const ll h = read<ll>();
		const int p = std::upper_bound( f + 1, f + C + 1, d * h ) - f;
		printf( "%d ", ( p == C + 1 )? -1: p );
	}
}
