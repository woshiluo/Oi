/*
 * b.cpp
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

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		static int a[N], res[N];
		std::vector<int> b[2];
		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
		}
		static char str[N];
		scanf( "%s", str + 1 );
		for( int i = 1; i <= n; i ++ ) {
			if( str[i] == '0' ) 
				b[0].push_back(i);
			else
				b[1].push_back(i);
		}
		std::sort( b[0].begin(), b[0].end(), []( const int _a, const int _b ) { return a[_a] < a[_b]; } );
		std::sort( b[1].begin(), b[1].end(), []( const int _a, const int _b ) { return a[_a] < a[_b]; } );
		int p = 0;
		for( auto pos: b[0] ) {
			p ++;
			res[pos] = p;
		}
		for( auto pos: b[1] ) {
			p ++;
			res[pos] = p;
		}

		for( int i = 1; i <= n; i ++ ) {
			printf( "%d ", res[i] );
		}
		printf( "\n" );
	}
}
