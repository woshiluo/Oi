/*
 * luogu.1315.cpp
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

int main() {
	int n, m, k;
	n = read<int>(); m = read<int>(); k = read<int>();
	for( int i = 1; i < n; i ++ ) 
		a[i] = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		int t, u, v;
		t = read<int>(); u = read<int>(); v = read<int>();
		seg.push_back( (Seg) { t, u, v } );
		chk_Max( start[u], t );
		sum[u] ++; sum[v] --;
	}
	for( int i = 1; i < n - 1; i ++ ) {
		a[i] -= start[ i + 1 ] - start[i];
		if( a[i] < 0 )
			a[i] = 0;
	}

	std::priority_queue<int> q;
}
