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
const ll LLF = 0x3f3f3f3f3f3f3f3f;

int a[N];

int main() {
	int T = read<int>();
	while( T -- ) {
		int n = read<int>(), k = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
		}
		ll ans = -LLF;
		for( int i = 1; i <= Min( n, 5000 ); i ++ ) {
			for( int j = i + 1; j <= Min( n, 5000 ); j ++ ) 
				chk_Max( ans, 1LL * i * j - 1LL * k * ( a[i] | a[j] ) );
		}
		for( int i = 1; i < n; i ++ ) {
			chk_Max( ans, 1LL * i * ( i + 1 ) - 1LL * k * ( a[i] | a[ i + 1 ] ) );
		}
		printf( "%lld\n", ans );
	}
}
