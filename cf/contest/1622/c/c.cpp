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

const int N = 2e5 + 1e4;

void work() {
	static int a[N];
	static ll sum[N];
	int n = read<int>();
	ll k = read<ll>();
	for( int i = 1; i <= n; i ++ ) 
		a[i] = read<int>();
	std::sort( a + 1, a + n + 1 );
	for( int i = 1; i <= n; i ++ )
		sum[i] = sum[ i - 1 ] + (ll)a[i];

	auto len = []( int left, int rig ) { 
		if( rig < left ) 
			return 0;
		return rig - left + 1;
	};
	auto get_sum = [n]( int left, int rig ) { 
		if( rig > n ) 
			return 0LL;
		if( rig < left ) 
			return 0LL;
		return sum[rig] - sum[ left - 1 ]; 
	};

	auto get_need = [n, k, get_sum, len]( int fval ) {
		int left = 1, rig = n, res = n + 1;
		while( left <= rig ) {
			int mid = ( left + rig ) >> 1;
			if( get_sum( 2, mid ) + 1LL * fval * ( len( mid + 1, n ) + 1 ) <= k ) {
				res = mid;
				left = mid + 1;
			}
			else
				rig = mid - 1;
		}
		if( res > n || get_sum( 2, res ) + 1LL * fval * ( len( res + 1, n ) + 1 ) > k ) 
			return n + 1;
		// printf( "%lld\n", get_sum( 2, res ) + 1LL * fval * ( len( res + 1, n ) + 1 ) );
		return len( res + 1, n );
	};

	auto get_step = [n, k, get_sum, len]( int fval ) {
		int left = 1, rig = n, res = n + 1;
		while( left <= rig ) {
			int mid = ( left + rig ) >> 1;
			if( get_sum( 2, mid ) + 1LL * fval * ( len( mid + 1, n ) + 1 ) <= k ) {
				res = mid;
				left = mid + 1;
			}
			else
				rig = mid - 1;
		}
		if( get_sum( 2, res ) + 1LL * fval * ( len( res + 1, n ) + 1 ) > k ) 
			return (ll)(1e18);
		return 1LL * ( a[1] - fval ) + 1LL * len( res + 1, n );
	};


	ll ans = get_step(0);
	for( int i = 0; i < n; i ++ ) {
		int left = (int)(-1e7), rig = a[1], res = 0;
		while( left <= rig ) {
			int mid = ( left + rig ) >> 1;
			if( get_need(mid) <= i ) {
				res = mid;
				left = mid + 1;
			}
			else {
				rig = mid - 1;
			}
		}
		if( get_need(res) <= i )
			chk_Min( ans, get_step(res) );
	}

	printf( "%lld\n", ans );
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		work();
	}
}
