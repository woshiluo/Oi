/*
 * d.cpp
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

#include <vector>
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

const int N = 2e5 + 1e4;

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt = 1;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int col[N], id[N];
bool vis[N];

inline int lowbit( int cur ) { return cur & ( -cur ); }

void dfs( int cur, int la ) {
	col[cur] = col[la] ^ 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, cur );
	}
}

void work() {
	int n = read<int>();

	ecnt = 1;
	for( int i = 0; i <= n; i ++ ) {
		ehead[i] = vis[i] = vis[ i << 1 ] = 0;
	}

	for( int i = 1; i < n; i ++ ) {
		int u, v;
		u = read<int>(); v = read<int>();
		add_edge( u, v );
		add_edge( v, u );
	}

	dfs( 1, 0 );

	int cnt[2];
	cnt[0] = cnt[1] = 0;
	for( int i = 1; i <= n; i ++ ) {
		cnt[ col[i] ] ++;
	}
	std::vector<int> allowed[2];
	int p = ( cnt[1] < cnt[0] );
	int tot = cnt[p];
	while(tot) {
		int left = lowbit(tot);
		int rig = ( left << 1 ) - 1;
		for( int i = left; i <= rig; i ++ ) {
			vis[i] = true;
			allowed[p].push_back(i);
		}
		tot -= lowbit(tot);
	}

	for( int i = 1; i <= n; i ++ ) {
		if( !vis[i] ) 
			allowed[ p ^ 1 ].push_back(i);
	}
	for( int i = 1; i <= n; i ++ ) {
		id[i] = allowed[ col[i] ].back();
		allowed[ col[i] ].pop_back();
	}
	for( int i = 1; i <= n; i ++ ) {
		printf( "%d ", id[i] );
	}
	printf( "\n" );
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		work();
	}
}
