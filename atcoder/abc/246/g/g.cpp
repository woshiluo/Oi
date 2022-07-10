/*
 * g.cpp
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

struct Edge { int to, next; } e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int a[N];
int f[N];

int b( const int pos, const int lim ) { return a[pos] >= lim; }

void dfs( const int cur, const int la, const int lim ) {
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, cur, lim );
		f[cur] += f[ e[i].to ];
	}
	f[cur] -= 1;
	chk_Max( f[cur], 0 );
	f[cur] += b( cur, lim );
}

bool check( const int val ) {
	memset( f, 0, sizeof(f) );
	dfs( 1, 0, val );
	return f[1] == 0;
}

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif
	const int n = read<int>();
	for( int i = 2; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		u = read<int>(); v = read<int>();
		add_edge( u, v );
		add_edge( v, u );
	}

	int left = 0, rig = (int)(1e9);
	int res = rig;
	while( left <= rig ) {
		const int mid = ( left + rig ) >> 1;
		if( check(mid) ) 
			rig = mid - 1;
		else {
			left = mid + 1;
			res = mid;
		}
	}

	printf( "%d\n", res );
}
