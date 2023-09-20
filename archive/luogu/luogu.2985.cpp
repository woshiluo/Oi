/*
 * luogu.2985.cpp 2023-07-13
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <algorithm>

typedef const int cint;
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

const int N = 5e4 + 1e3;

int happy[N], day[N];

bool check( const ll limit, cint n, cint d ) {
	int p = 0;
	ll cur = 0;
	for( int i = 1; i <= d; i ++, cur >>= 1LL ) {
		while( p <= n && cur < limit ) {
			cur += happy[p];
			day[p] = i;
			p ++;
		}
		if( cur < limit ) 
			return false;
	}
	while( p <= n ) {
		day[p] = d;
		p ++;
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.2985.in", "r", stdin );
	freopen( "luogu.2985.out", "w", stdout );
#endif

	cint n = read<int>();
	cint d = read<int>();

	ll sum = 0;

	for( int i = 1; i <= n; i ++ ) {
		happy[i] = read<int>();
		sum += happy[i];
	}

	ll left = 0, rig = sum, res = 0;;
	while( left <= rig ) {
		const ll mid = ( left + rig ) >> 1LL;

		if( check( mid, n, d ) ) {
			res = mid;
			left = mid + 1;
		}
		else
			rig = mid - 1;
	}

	check( res, n, d );
	printf( "%lld\n", res );
	for( int i = 1; i <= n; i ++ ) {
		printf( "%d\n", day[i] );
	}
}
