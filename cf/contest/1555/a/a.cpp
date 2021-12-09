/*
 * a.cpp
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

const int INF = 0x3f3f3f3f;

int f[1100];

int dfs( int cur ) {
	if( f[cur] ) 
		return f[cur];
	int res = INF;
	for( int i = 1; i < cur; i ++ ) {
		chk_Min( res, dfs(i) + dfs( cur - i ) );
	}
	f[cur] = res;
	return res;
}

int main() {
	f[6] = 15; f[8] = 20; f[10] = 25;
	for( int i = 1; i <= 6; i ++ ) 
		f[i] = 15;
	for( int i = 1; i <= 1000; i ++ ) 
		dfs(i);

	int T = read<int>(); 
	while( T -- ) {
		ll n = read<ll>();
		printf( "%lld\n", cur * 15LL );
	}
}
