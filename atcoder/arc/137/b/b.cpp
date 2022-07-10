/*
 * b.cpp
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

#include <map>
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

const int N = 1e6 + 1e5;

int a[N], sum[N], s[N];

std::map<int, int> mp;

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		if( a[i] == 0 ) 
			a[i] = 1;
		else
			a[i] = -1;
	}
	for( int i = n; i >= 1; i -- ) 
		sum[i] = sum[ i + 1 ] + a[i];
	for( int i = 1; i <= n; i ++ ) 
		mp[ sum[i] ] ++;
	int base = n + 1;
	s[base] = 1; s[ base + 1 ] = -1;
	for( int i = n; i >= 1; i -- ) {
		s[ base + mp.begin() -> first ] ++;
		s[ base + ( -- mp.end() ) -> first  + 1 ] --;
		base -= a[i];
		mp[ sum[i] ] --;
		if( mp[ sum[i] ] == 0 ) 
			mp.erase( sum[i] );
	}
	int ans = 0;
	for( int i = 1; i <= n + n + n; i ++ ) {
		s[i] += s[ i - 1 ];
		if( s[i] != 0 ) 
			ans ++;
	}
	printf( "%d\n", ans );
}
