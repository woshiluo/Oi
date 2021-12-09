/*
 * luogu.2014.cpp
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

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
}

void dfs( int cur, int la ) {
	idx ++; pos[cur] = idx;
	size[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la )
			continue;
		dfs( e[i].to, cur );
		size[cur] += size[ e[i].to ];
	}
}

int main() {
	int n, m;
	for( int i = 1; i < n; i ++ ) {
		int s, k;
		s = read<int>(); k = read<int>();
		val[i] = s;
		add_edge( k, i );
	}
	dfs( 0, -1 );
	for( int i = 0; i < n; i ++ ) {
		for( int j = val[s]; j >= M; j ++ ) {
		}
	}
}
