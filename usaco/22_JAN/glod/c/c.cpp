/*
 * c.cpp
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

#include <queue>
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

const int N = 1e5 + 1e4;

int in[N];

struct Edge {
	int to, next, val;
} e[ N << 2 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to, int val ) {
	ecnt ++;
	in[to] ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int d[N], a[N], dis[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		d[i] = read<int>();
	}
	{
		int p = 1, cnt = 0;
		while( p <= n ) {
			int tmp = p; 
			for( ; p <= d[tmp]; p ++ ) 
				a[p] = cnt;
			p = d[tmp] + 1;
			cnt ++;
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		if( i + 1 <= n && a[ i + 1 ] - a[i] == 0 )
			add_edge( i, i + 1, 0 );
		if( d[i] + 1 <= n && a[ d[i] + 1 ] - a[i] == 1 ) 
			add_edge( i, d[i] + 1, 1 );
		if( a[i] - a[ d[i] ] == -1 ) 
			add_edge( d[i], i, 0 );
	}

	std::queue<int> q;
	for( int i = 1; i <= n; i ++ ) 
		if( in[i] == 0 ) 
			q.push(i);
	while( !q.empty() ) {
		int cur = q.front(); q.pop();
		for( int i = ehead[cur]; i; i = e[i].next ) {
			int to = e[i].to;
			chk_Max( dis[to], dis[cur] + e[i].val );
			in[to] --;
			if( in[to] == 0 ) 
				q.push(to);
		}
	}

	printf( "%d\n", n + 1 );
	for( int i = 1; i <= n; i ++ ) 
		printf( "%lld\n", 1LL * a[i] * (ll)( n + 1 ) + 1LL * dis[i] );
}
