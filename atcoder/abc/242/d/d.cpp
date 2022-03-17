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

const int N = 1e5 + 1e4;

int a[N];
int son[5][2];

int dfs( ll cur, ll depth ) {
	if( cur == 1 ) {
		return ( a[1] + depth ) % 3;
	}
	if( depth == 0 ) {
		return a[cur];
	}
	return son[ dfs( ( cur >> 1 ) + ( cur & 1 ), depth - 1 ) ][ cur % 2 == 0 ];
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	static char str[N];
	son[0][0] = 1; son[0][1] = 2;
	son[1][0] = 2; son[1][1] = 0;
	son[2][0] = 0; son[2][1] = 1;

	scanf( "%s", str + 1 );
	int n = strlen( str + 1 );
	for( int i = 1; i <= n; i ++ ) 
		a[i] = str[i] - 'A';

	int Q = read<int>();
	while( Q -- ) {
		ll t, k;
		t = read<ll>(); k = read<ll>();
		printf( "%c\n", dfs( k, t ) + 'A' );
	}
}
