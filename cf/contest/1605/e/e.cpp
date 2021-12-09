/*
 * e.cpp
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


template <class T>
T aabs( T a ) { return a < 0? -a: a; }
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

int a[N], b[N], c[N], add[N], mu[N];
std::vector<ll> sum;

void get_mu() {
	mu[1] = 1;
	for( int i = 2; i < N; i ++ ) {
		mu[i] --;
		for( int j = i * 2; j < N; j += i ) {
			mu[j] -= mu[i];
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	get_mu();
	int n = read<int>();
	ll ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		b[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ )
		c[i] = b[i] - a[i];
	c[1] = 0;
	for( int i = 1; i <= n; i ++ ) {
		int d = c[i];
		for( int j = i; j <= n; j += i ) 
			c[j] -= d;
		add[i] = d;
	}

	for( int i = 1; i <= n; i ++ ) {
		if( mu[i] == 0 ) 
			ans += aabs( add[i] );
		else 
			sum.push_back( mu[i] * add[i] );
	}
	std::sort( sum.begin(), sum.end() );

	int size = sum.size();
	for( int i = 1; i < size; i ++ ) 
		sum[i] += sum[ i - 1 ];

	auto len = []( const int left, const int rig ) { 
		if( rig < left ) 
			return 0;
		return rig - left + 1; 
	};
	auto check = []( const int cur ) { 
		if( cur == 0 ) 
			return sum[cur];
		return sum[cur] - sum[ cur - 1 ]; 
	};
	auto query = []( const int left, const int rig ) { 
		if( rig < left ) 
			return 0LL;
		if( left == 0 ) 
			return sum[rig];
		return sum[rig] - sum[ left - 1 ]; 
	};

	int q = read<int>();
	while( q -- ) {
		int x = read<int>();
		x -= a[1];
		int left = 0, rig = size - 1, res = -1;
		while( left <= rig ) {
			int mid = ( left + rig ) >> 1;
			if( check(mid) <= -x ) {
				res = mid;
				left = mid + 1;
			}
			else
				rig = mid - 1;
		}
		ll ans2 = query( res + 1, size - 1 ) + 1LL * len( res + 1, size - 1 ) * x;
		ans2 -= query( 0, res ) + 1LL * len( 0, res ) * x;
		printf( "%lld\n", ans + ans2 );
	}
}
