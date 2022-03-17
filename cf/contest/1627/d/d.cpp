/*
 * d.cpp
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

const int MAX = 1e6 + 1e5;
const int N = MAX + 10;

bool vis[N];

int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		vis[ read<int>() ] = 1;
	}
	for( int i = MAX; i >= 1; i -- ) {
		if( vis[i] ) 
			continue;
		std::vector<int> a;
		for( int j = 1; 1LL * j * i <= MAX; j ++ ) {
			if( vis[ i * j ] )
				a.push_back(j);
		}
		if( a.size() <= 1 ) 
			continue;
		int g = a.front();
		for( auto &cur: a ) {
			g = gcd( g, cur );
		}
		if( g == 1 ) 
			vis[i] = true;
	}
	int cnt = 0;
	for( int i = 1; i <= MAX; i ++ ) {
		cnt += vis[i];
	}
	printf( "%d\n", cnt - n );
}
