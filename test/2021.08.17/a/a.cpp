/*
 * a.cpp
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

const int N = 2e5 + 1e4;
const int INF = 0x3f3f3f3f;

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

const char wanted[5] = { 0, 'w', 's', 'd', 'm' };
void work( const char str[], int left, int rig ) {
	static int f[2][6];
	// 0 none
	// 1 w
	// 2 s 
	// 3 d
	// 4 m
	// 5 end
	memset( f, INF, sizeof(f) );
	int cur = 0, la = 1;
	f[la][0] = 0;
	for( int i = left; i <= rig; i ++ ) {
		for( int j = 0; j < 5; j ++ ) {
			f[cur][j] = f[la][j];

			if( j >= 3 && str[i] == 'q' ) {
				f[cur][j] = f[la][j] + 1;
				continue;
			}

			if( j <= 3 && str[i] == wanted[ j + 1 ] ) 
				f[cur][j] = f[la][j] + 1;

			if( j > 0 && j <= 4 && str[i] == wanted[j] ) 
				chk_Min( f[cur][j], f[la][ j - 1 ] );
		}
		cur ^= 1; la ^= 1;
	}

	int res = f[la][4];
	printf( "%d\n", res >= INF ? -1: res );
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int n, m;
	char str[N];
	scanf( "%d%d", &n, &m );
	scanf( "%s", str + 1 );
	while( m -- ) {
		int opt;
		scanf( "%d", &opt );
		if( opt == 1 ) {
			int x; char y[3];
			scanf( "%d%s", &x, y );
			str[x] = y[0];
		}
		else {
			int x, y;
			scanf( "%d%d", &x, &y );
			work( str, x, y );
		}
	}
}
