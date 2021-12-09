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

const int N = 5100;
const int INF = 0x3f3f3f3f;
const ll LNF = 0x3f3f3f3f3f3f3f3f;

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
	for (; !isdigit(ch); ch = getchar())
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

int n, q;
int val[N];
ll f[N][N];

struct ForceOnline {
	ll lastans;
	int i, c;
	void get_ans( ll ans ) {
		lastans = ans;
		printf( "%lld ", ans );
	}
	void update( int _i, int _c ) {
		i = ( (ll)_i + lastans ) % n + 1;
		c = ( (ll)_c + lastans ) % n + 1;
	}
} fo;

void query( int cur, int k ) {
	fo.get_ans( f[ n - cur + 1 ][k] );
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	n = read<int>(); q = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		val[ n - i + 1 ] = read<int>();
	}
	memset( f, -INF, sizeof(f) );
	f[0][0] = 0;
	for( int j = 1; j <= n; j ++ ) {
		int la_max = 0;
		for( int i = 1; i <= n; i ++ ) {
			f[i][j] = f[la_max][ j - 1 ] + val[i];
			if( f[ i - 1 ][ j - 1 ] >= f[ la_max ][ j - 1 ] ) 
				la_max = i - 1;
		}
		for( int i = 1; i <= n; i ++ ) {
			chk_Max( f[i][j], f[ i - 1 ][j] );
		}
	}

	while( q -- ) {
		int _i, _c;
		_i = read<int>(); _c = read<int>();
		fo.update( _i, _c );
		query( fo.i, fo.c );
	}
}
