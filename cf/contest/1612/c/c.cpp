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

ll dx( int left, int rig ) { return ( left + rig ) * ( rig - left + 1LL ) / 2LL; }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		ll k, x;
		k = read<ll>(); x = read<ll>();
		ll ans = 0;
		{
		int left = 1, rig = k, res = 0;
		while( left <= rig ) {
			int mid = ( left + rig ) >> 1;
			if( dx( 1, mid ) < x ) {
				res = mid;
				left = mid + 1;
			}
			else
				rig = mid - 1;
		}
		if( res != k ) {
			ans += res + 1;
			printf( "%lld\n", ans );
			continue;
		}
		}
		ans += k;
		x -= dx( 1, k );
		int left = 1, rig = k - 1, res = 0;
		while( left <= rig ) {
			int mid = ( left + rig ) >> 1;
			if( dx( k - 1 - mid + 1, k - 1 ) < x ) {
				res = mid;
				left = mid + 1;
			}
			else
				rig = mid - 1;
		}
		if( res != k - 1 ) 
			ans += res + 1;
		else

			ans += k - 1;
		printf( "%lld\n", ans );
	}
}
