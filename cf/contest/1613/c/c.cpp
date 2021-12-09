/*
 * c.cpp
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

const int N = 110;

int n; ll h;
ll a[N];

ll check( ll k ) {
	ll tot = 0;
	for( int i = 1; i < n; i ++ ) {
		tot += Min( a[ i + 1 ] - 1 , a[i] - 1 + k ) - a[i] + 1;
	}
	return tot;
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		n = read<int>(); h = read<ll>();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
		}
		a[ n + 1 ] = (ll)(2e18); n ++;

		ll left = 1, rig = h, res = h;
		while( left <= rig ) {
			ll mid = ( left + rig ) >> 1LL;
			if( check(mid) >= h ) {
				res = mid;
				rig = mid - 1;
			}
			else
				left = mid + 1;
		}
		printf( "%lld\n", res );
	}
}
