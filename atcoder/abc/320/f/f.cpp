/*
 * f.cpp 2023-09-17
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

const int N = 310;
const int INF = 0x3f3f3f3f;

int f[N][N][N][N];


int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	struct Station {
		int x, f, p;
	};
	cint n = read<int>();
	cint h = read<int>();
	std::vector<Station> stations( n + 1, { 0, 0, 0 } );
	for( int i = 1; i <= n; i ++ ) {
		stations[i].x = read<int>();
	}
	for( int i = 1; i < n; i ++ ) {
		stations[i].p = read<int>();
		stations[i].f = read<int>();
	}

	auto diff = [&]( cint from, cint to ) { return stations[to].x = stations[from].x; };
	memset( f, INF, sizeof(f) );
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j <= h; j ++ ) {
			for( int k = 0; k <= h; k ++ ) {
				f[i][i][j][k] = 0;
			}
		}
	}
	for( int len = 2; len <= n; len ++) {
		for( int left = 1, rig = left + len - 1;
				rig <= n;
				left ++, rig ++ ) {
			for( int p1 = 0; p1 <= h; p1 ++ ) {
				for( int p2 = 0; p2 <= h; p2 ++ ) {
					if( p1 - diff( left, left + 1 ) >= 0 )
						chk_Min( f[left][rig][p1][p2], f[ left + 1 ][rig][ p1 - diff( left, left + 1 ) ][p2] );
					if( stations[left].f + p1 - diff( left, left + 1 ) >= 0 )
						chk_Min( f[left][rig][p1][p2], f[ left + 1 ][rig][ p1 - diff( left, left + 1 ) ][p2] );
					chk_Min( f[left][rig][p1][p2], f[ left + 1 ][rig][ Min( p1 - diff( left, left + 1 ) + stations[left].f, h ) ][p2] + stations[left].p );
					if( p2 - diff( rig - 1, rig ) >= 0 )
						chk_Min( f[left][rig][p1][p2], f[left][ rig - 1 ][p1][ p2 - diff( rig - 1, rig ) ] );
					if( p2 - diff( rig - 1, rig ) + stations[rig].f >= 0 )
						chk_Min( f[left][rig][p1][p2], f[left][ rig - 1 ][p1][ Min( p2 - diff( rig - 1, rig ) + stations[rig].f, h ) ] + stations[rig].p );
				}
			}
		}
	}

	int res = INF;
	for( int i = 0; i <= h; i ++ ) 
		chk_Min( res, f[1][n][0][i] );

	if( res == INF )
		printf( "-1\n" );
	else
		printf( "%d\n", res );
}
