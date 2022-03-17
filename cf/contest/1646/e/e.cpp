/*
 * e.cpp
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

ll _gcd( ll a, ll b ) { return b? _gcd( b, a % b ): a; }
ll _lcm( ll a, ll b ) {
	ll k = _gcd( a, b );
	return a / k * b;
}

int full_pow( const int k ) { return 1 << k; }
bool chk_pos( const int s, const int k ) { return ( s >> k ) & 1; }

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n, m;
	ll ans = 1;
	n = read<int>(); m = read<int>();

	std::vector<bool> vis;
	vis.resize( n + 1, true );
	for( int i = 2; i <= n; i ++ ) {
		if( !vis[i] ) 
			continue;
		ll p = 1;
		for( ll j = 1LL * i * i; j <= n; j *= 1LL * i ) {
			vis[j] = false;
			p ++;
		}
		for( int s = 1; s < full_pow(p); s ++ ) {
			int min = -1;
			ll lcm = 1;
			int bit_cnt = 0;
			for( int k = 0; k < p; k ++ ) {
				if( chk_pos( s, k ) ) {
					bit_cnt ++;
					if( min == -1 ) 
						min = k + 1;
					lcm = Min( 1LL * ( p + 1 ) * m, _lcm( k + 1, lcm ) );
				}
			}
			ans += 1LL * ( ( bit_cnt & 1 )? 1: -1 ) * ( min * m / lcm );
		}
	}
	printf( "%lld\n", ans );
}
