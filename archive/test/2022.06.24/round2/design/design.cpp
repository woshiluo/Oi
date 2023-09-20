/*
 * design.cpp
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

const int N = 5100;
const int INF = 0x3f3f3f3f;

int d[N], sum[N];
int f[N][N];

int main() {
	freopen( "design.in", "r", stdin );
	freopen( "design.out", "w", stdout );

	cint n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		d[i] = read<int>();
		sum[i] = sum[ i - 1 ] + d[i];
	}

	auto query = [] ( cint left, cint rig ) { 
		if( left == 0 ) 
			return sum[rig];
		return sum[rig] - sum[ left - 1 ];
	};

	memset( f, -INF, sizeof(f) );
	f[0][0] = 0;
	for( int i = 0; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) 
			chk_Max( f[i][j], f[i][ j - 1 ] );
		int p = i, diff = 0;
		bool current_diff = false;
		for( int j = i + 1; j <= n; j ++ ) {
			if( p <= 1 )
				chk_Max( f[j][ i + 1 ], f[i][p] + diff - current_diff );
			else
				chk_Max( f[j][ i + 1 ], Max( f[i][p] + diff - current_diff, f[i][ p - 1 ] + diff ) );

			while( p > 1 && query( p, i ) < query( i + 1, j ) ) {
				p --;
				current_diff = false;
			}
			if( query( p, i ) == query( i + 1, j ) ) {
				diff ++;
				current_diff = true;
			}
		}
		for( int j = 0; j <= n; j ++ ) 
			printf( "%4d ", f[i][j] < 0? -1: f[i][j] );
		printf( "\n" );
	}

	int res = 0;
	for( int i = 0; i <= n; i ++ ) 
		chk_Max( res, f[n][i] );

	printf( "%d\n", res );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
