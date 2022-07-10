/*
 * e.cpp
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

#include <set>
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

const int N = 1e5 + 1e4;

int col, id[N], cnt[N];
int f[N][2], pos[N][2];
bool vis[N];

void dfs( int cur, int p ) {
	if( vis[ f[cur][p] ] ) 
		return ;
	vis[ f[cur][p] ] = true;
	id[ f[cur][p] ] = col;
	dfs( cur, p ^ 1 );
	dfs( pos[ f[cur][p] ][ p ^ 1 ], p );
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		col = 0;
		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			f[i][0] = read<int>();
			pos[ f[i][0] ][0] = i;
		}
		for( int i = 1; i <= n; i ++ ) {
			f[i][1] = read<int>();
			pos[ f[i][1] ][1] = i;
		}

		for( int i = 1; i <= n; i ++ ) {
			id[i] = vis[i] = 0;
			cnt[i] = 0;
		}

		for( int i = 1; i <= n; i ++ ) {
			if( vis[i] ) 
				continue;
			col ++;
			dfs( pos[i][0], 0 );
		}

		for( int i = 1; i <= n; i ++ ) 
			cnt[ id[i] ] ++;

		int res = 0;

		for( int i = 1; i <= col; i ++ ) {
			if( cnt[i] & 1 ) 
				res ++;
		}

		ll ans = 0;
		for( int i = 0; i < ( n - res ) / 2; i ++ ) {
			ans += n - i - 1;
			ans -= i;
		}

		printf( "%lld\n", ans * 2LL );
	}
}
