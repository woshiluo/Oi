/*
 * luogu.1396.cpp
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

#include <queue>
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

const int N = 1e4 + 1e3;
const int M = 2e4 + 1e3;

struct Edge {
	int to, next, val;
} e[M << 1];
int ehead[N], ecnt;
void add_edge( cint from, cint to, cint val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

bool check( int st, int ed, int limit ) {
	std::queue<int> q;
	static bool vis[N];
	memset( vis, 0, sizeof(vis) );

	q.push(st); vis[st] = true;
	while( !q.empty() ) {
		cint cur = q.front(); q.pop();
		for( int i = ehead[cur]; i; i = e[i].next ) {
			cint to = e[i].to;
			if( e[i].val > limit || vis[to] ) 
				continue;
			vis[to] = true;
			q.push(to);
		}
	}

	return vis[ed];
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1396.in", "r", stdin );
	freopen( "luogu.1396.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();
	cint s = read<int>();
	cint t = read<int>();
	

	for( int i = 1; i <= m; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();
		cint w = read<int>();

		add_edge( u, v, w );
		add_edge( v, u, w );
	}

	int left = 1, rig = 1e4, res = 0;

	while( left <= rig ) {
		cint mid = ( left + rig ) >> 1;
		if( check( s, t, mid ) ) {
			res = mid;
			rig = mid - 1;
		}
		else
			left = mid + 1;
	}

	printf( "%d\n", res );
}
