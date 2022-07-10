/*
 * f.cpp
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

const int N = 2e5 + 1e4;
const int K = 20;

int gcd( cint a, cint b ) { return b? gcd( b, a % b ): a; }
ll lcm( cint a, cint b ) { return 1LL * a / gcd( a, b ) * b; }
int aabs( cint cur ) { return cur < 0? -cur: cur; }

struct STTable {/*{{{*/
	int f[N][K];

	int merge( cint &a, cint &b ) { return gcd( a, b ); }

	void init( cint n, cint a[] ) {
		for( int i = 1; i <= n; i ++ ) 
			f[i][0] = a[i];
		for( int k = 1; k < K; k ++ ) {
			for( int i = 1; i <= n; i ++ ) 
				if( i + ( 1 << ( k - 1 ) ) <= n ) 
					f[i][k] = merge( f[i][ k - 1 ], f[ i + ( 1 << ( k - 1 ) ) ][ k - 1 ] );
		}
	}

	int query( cint l, cint r ) {
		if( r < l ) 
			return 0;
		cint p = ( std::log( r - l + 1 ) / std::log(2) );
		return merge( f[l][p], f[ r - ( 1 << p ) + 1 ][p] );
	}
} st_a, st_b, st_da, st_db;/*}}}*/

int a[N], b[N], da[N], db[N];

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	cint n = read<int>();
	cint q = read<int>();
	for( int i = 1; i <= n; i ++ ) 
		a[i] = read<int>();
	for( int i = 1; i <= n; i ++ ) 
		b[i] = read<int>();
	for( int i = 1; i < n; i ++ )
		da[i] = aabs( a[i] - a[ i + 1 ] );
	for( int i = 1; i < n; i ++ )
		db[i] = aabs( b[i] - b[ i + 1 ] );

	st_a.init( n, a ); st_b.init( n, b );
	st_da.init( n, da ); st_db.init( n, db );

	for( int _ = 1; _ <= q; _ ++ ) {
		cint l1 = read<int>();
		cint r1 = read<int>();
		cint l2 = read<int>();
		cint r2 = read<int>();
		
		cint p1 = gcd( st_a.query( l1, r1 ), st_b.query( l2, r2 ) );
		int p2 = 1;
		{
			p2 = gcd( st_da.query( l1, r1 - 1 ), st_db.query( l2, r2 - 1 ) );
			p2 = gcd( a[l1] + b[l2], p2 );
		}

		printf( "%lld\n", lcm( p1, p2 ) );
	}
}
