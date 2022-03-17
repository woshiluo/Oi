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

const int N = 310;
const int BASE = 110;

int main() {
	int T = read<int>();
	while( T -- ) {
		std::vector<int> cnt;
		std::vector<bool> vis;
		cnt.resize(N + 1);
		vis.resize(N + 1);
		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			cnt[ BASE + read<int>() ] ++;
		}
		for( int i = 0; i < N; i ++ ) {
			if( cnt[i] ) 
				vis[i] = true;
			if( cnt[i] > 1 ) {
				if( i < BASE ) 
					vis[ BASE + ( BASE - i ) ] = true;
				if( i > BASE ) 
					vis[ BASE - ( i - BASE ) ] = true;
			}
		}
		int ans = 0;
		for( int i = 0; i < N; i ++ ) 
			ans += vis[i];
		printf( "%d\n", ans );
	}
}
