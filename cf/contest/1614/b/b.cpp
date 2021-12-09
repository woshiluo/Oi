/*
 * b.cpp
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

const int N = 2e5 + 1e4;

struct Node { int val, id; };

int x[N];
Node a[N];

template <class T>
T aabs( T a ) { return a < 0? -a: a; }

int main() {
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			int tmp = read<int>();
			a[i] = (Node){ tmp, i };
		}
		std::sort( a + 1, a + n + 1, []( const Node _a, const Node _b ) { return _a.val > _b.val; } );
		x[0] = 0;
		for( int i = 1; i <= n; i ++ ) {
			x[ a[i].id ] = ( ( i >> 1 ) + ( i & 1 ) ) * ( ( i & 1 )? 1: -1 );
		}
		ll ans = 0;
		for( int i = 1; i <= n; i ++ ) {
			ans += 2LL * aabs( x[ a[i].id ] ) * a[i].val;
		}
		printf( "%lld\n", ans );
		for( int i = 0; i <= n; i ++ ) 
			printf( "%d ", x[i] );
		printf( "\n" );
	}
}
