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
	ll n = read<ll>();
	ll res = 0;
	for( ; pow( res, 3 ) < n; res ++ );
	const ll max = pow( res, 3 );
	if( max == n ) {
		printf( "%lld\n", max );
		return 0;
	}
	ll ans = max;
	ll p2 = (int)(1e6);
	for( ll p1 = 0; p1 <= (int)(1e6); p1 ++ ) {
		auto f = []( const ll p1, const ll p2 ) { return pow( p1, 3 ) + pow( p2, 3 ) + p1 * p1 * p2 + p1 * p2 * p2; };
		while( f( p1, p2 ) >= n && p2 > 0 ) {
			chk_Min( ans, f( p1, p2 ) );
			p2 --;
		}
	}
	printf( "%lld\n", ans );
}
