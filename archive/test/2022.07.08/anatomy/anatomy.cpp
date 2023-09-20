/*
 * anatomy.cpp
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

const int N = 18;
const int INF = 0x3f3f3f3f;
const ll LLF = 0x3f3f3f3f3f3f3f3f;

struct Edge {
	int to, next, val;
} e[ N * N ];
int ehead[N], ecnt = 1; 
void add_edge( cint cur, cint to, cint val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int full_pow( cint cur ) { return 1 << ( cur - 1 ); }
bool chk_pos( cint cur, cint pos ) { return cur & full_pow(pos); }

int g[N][N];
ll f[ 1 << ( N - 1 ) ][N][N];
// status / ed / cur

int main() {
#ifdef woshiluo
	freopen( "anatomy.in", "r", stdin );
	freopen( "anatomy.out", "w", stdout );
#endif

	cint n = read<int>();

	ll base = 0;
	{/*{{{*/
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= n; j ++ ) {
				g[i][j] = read<int>();
			}
		}

		for( int i = 1; i <= n; i ++ ) {
			for( int j = i + 1; j <= n; j ++ ) {
				if( g[i][j] == -1 ) {
					g[i][j] = g[j][i] = INF;
					continue;
				}
				cint d = Min( g[i][j], g[j][i] );
				g[i][j] -= d;
				g[j][i] -= d;
				base += d;
				add_edge( i, j, g[i][j] );
				add_edge( j, i, g[j][i] );
			}
		}
	}/*}}}*/


	memset( f, INF, sizeof(f) );
	for( int i = 1; i <= n; i ++ ) {
		f[ full_pow(i) ][0][0] = 0;
	}

	ll res = LLF;
	for( int st = 1; st < full_pow( n + 1 ); st ++ ) {
		for( int ed = 1; ed <= n; ed ++ ) {
			if( !chk_pos( st, ed ) ) 
				continue;
			for( int cur = 1; cur <= n; cur ++ ) {
				if( !chk_pos( st, cur ) )
					continue;
				for( int i = ehead[cur]; i; i = e[i].next ) {
					cint to = e[i].to;
					if( chk_pos( st, to ) )
						continue;
					cint nxt = ( st | full_pow(to) );

					chk_Min( f[nxt][ed][to], f[st][ed][cur] + g[cur][to] );
					chk_Min( f[nxt][0][0], f[nxt][ed][to] + g[to][ed] );

					chk_Min( f[nxt][ed][to], f[st][0][0] + g[cur][to] );
				}
				chk_Min( f[st][ed][cur], f[st][0][0] );
			}
		}
	}

	chk_Min( res, f[ full_pow( n + 1 ) - 1 ][0][0] );

	if( res >= INF ) 
		printf( "-1\n" );
	else
		printf( "%lld\n", base + res );
}
