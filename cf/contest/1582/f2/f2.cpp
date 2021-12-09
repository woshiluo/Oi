/*
 * f1.cpp
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

const int MAX_A = ( 1 << 13 );

int r[MAX_A];
bool vis[MAX_A];
std::vector<int> g[MAX_A];

int main() {
#ifdef woshiluo
	freopen( "f1.in", "r", stdin );
	freopen( "f1.out", "w", stdout );
#endif
	int n = read<int>();
	vis[0] = true;
	for( int i = 0; i < MAX_A; i ++ ) {
		r[i] = MAX_A - 1;
		g[i].push_back(0);
	}
	for( int i = 1; i <= n; i ++ ) {
		int cur = read<int>();
		for( auto &val: g[cur] ) {
			int nxt = val ^ cur;
			vis[nxt] = true;
			while( r[nxt] > cur ) {
				g[ r[nxt] ].push_back(nxt);
				r[nxt] --;
			}
		}
		g[cur] = {};
	}
	int res = 0;
	for( int i = 0; i < MAX_A; i ++ ) {
		res += vis[i];
	}
	printf( "%d\n", res );
	for( int i = 0; i < MAX_A; i ++ ) {
		if( vis[i] ) 
			printf( "%d ", i );
	}
}
