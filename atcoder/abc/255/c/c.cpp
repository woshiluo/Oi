/*
 * c.cpp
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

ll get( const ll a, const ll d, const ll n ) {
	return a + d * ( n - 1LL );
}

int main() {
	const ll x = read<ll>();
	ll a = read<ll>();
	ll d = read<ll>();
	const ll n = read<ll>();

	if( d < 0 ) {
		a = get( a, d, n );
		d = -d;
	}

	const ll lst = get( a, d, n );
	if( x > lst ) {
		printf( "%lld\n", x - lst );
		return 0;
	}
	if( x < a ) {
		printf( "%lld\n", a - x );
		return 0;
	}

	ll left = 1, rig = n, res = n;
	while( left <= rig ) {
		const ll mid = ( left + rig ) >> 1LL;
		if( get( a, d, mid ) >= x ) {
			res = mid;
			rig = mid - 1;
		}
		else
			left = mid + 1;
	}
	
	printf( "%lld\n", Min( get( a, d, res ) - x, x - get( a, d, res - 1 ) ) );
}
