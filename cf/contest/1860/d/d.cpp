/*
 * d.cpp 2023-08-19
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

#include <map>
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

const int N = 150;
const int INF = 0x3f3f3f3f;

int f[2][N][ N * N ];
// 10

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	static char str[N];
	scanf( "%s", str );

	cint n = strlen(str);
	int tot_0 = 0;
	for( int i = 0; i < n; i ++ )
		tot_0 += ( str[i] == '0' );

	memset( f, INF, sizeof(f) );
	int cur = 0, nxt = 1;
	f[cur][0][0] = ( str[0] != '1' );
	f[cur][1][0] = ( str[0] != '0' );
	for( int i = 0; i < n - 1; i ++, cur ^= 1, nxt ^= 1 ) {
		for( int j = 0; j <= n; j ++ )
			for( int k = 0; k <= n * n; k ++ ) {
				f[nxt][j][k] = INF;
			}
		for( int j = 0; j <= n; j ++ ) {
			for( int k = 0; k <= n * n; k ++ ) {
				if( f[cur][j][k] != INF ) {
					chk_Min( f[nxt][ j + 1 ][ k + i + 1 - j ], f[cur][j][k] + ( str[ i + 1 ] != '0' ) );
					chk_Min( f[nxt][j][k], f[cur][j][k] + ( str[ i + 1 ] != '1' ) );
				}
			}
		}
	}

	printf( "%d\n", f[cur][tot_0][ ( tot_0 * ( n - tot_0 ) ) >> 1 ] >> 1 );
}
