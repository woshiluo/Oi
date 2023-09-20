/*
 * loj.160.cpp
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

const int N = 5e4 + 1e3;

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int idx;
int pos[N], size[N], v[N], w[N];
std::vector<ll> f[N];

void dfs( int cur, int la ) {
	size[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, cur );
		size[cur] += size[ e[i].to ];
	}
	idx ++; pos[idx] = cur;
}

int main() {
#ifdef woshiluo
	freopen( "loj.160.in", "r", stdin );
	freopen( "loj.160.out", "w", stdout );
#endif
	int n, W;
	n = read<int>(); W = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		int tmp = read<int>();
		add_edge( tmp, i );
	}
	for( int i = 1; i <= n; i ++ ) {
		w[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		v[i] = read<int>();
	}
	dfs( 0, -1 );
	f[0].resize(W + 1);
	for( int i = 1; i <= idx; i ++ ) {
		f[i].resize(W + 1);
		for( int j = 0; j <= W; j ++ ) {
			int cur = pos[i];
			if( j >= w[cur] ) 
				f[i][j] = Max( f[ i - 1 ][ j - w[cur] ] + v[cur], f[ i - size[cur] ][j] );
			else
				f[i][j] = f[ i - size[cur] ][j];
		}
	}
	printf( "%lld\n", f[n][W] );
}
