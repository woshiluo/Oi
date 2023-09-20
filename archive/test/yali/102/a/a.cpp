/*
 * a.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <bitset>
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

inline int full_pow( int k ) { return ( 1 << k ); }

const int N = 1e7 + 1e2;

ll base = 1;
int pri[20];
ll sum[N];
ll mul[ ( 1 << 8 ) ], mul2[ ( 1 << 8 ) ];
bool p[ ( 1 << 10 ) ];


template <class T>
T gcd( T a, T b ) { return b? gcd( b, a % b ): a; }
template <class T>
T lcm( T a, T b ) { return a / gcd( a, b ) * b; }

bool is_prime( int cur ) {
	int sqrt = std::sqrt( cur );
	for( int i = 2; i <= sqrt; i ++ ) {
		if( cur % i == 0 ) 
			return false;
	}
	return true;
}

void init() {
	{
		int cur = 2, cnt = 0;
		while( cnt < 16 ) {
			if( is_prime(cur) ) {
				pri[cnt] = cur;
				cnt ++;
			}
			cur ++;
		}
	}

	const int MIN_N = 8;
	mul[0] = mul2[0] = 1;
	for( int i = 1; i < full_pow(MIN_N); i ++ ) {
		int cnt = 0;
		mul[i] = mul2[i] = 1;
		for( int j = 0; j < MIN_N; j ++ ) {
			if( i & ( 1 << j ) ) {
				cnt ++;
				mul[i] *= pri[j];
				mul2[i] *= pri[ j + 8 ];
			}
		}
		p[i] = ( cnt & 1 );
	}

	std::bitset<N> flag;
	for( int i = 0; i < MIN_N; i ++ ) {
		base *= pri[i];
	}

	for( int i = 0; i < MIN_N; i ++ ) {
		for( int j = 0; j <= base; j += pri[i] ) {
			flag[j] = true;
		}
	}

	for( int i = 1; i <= base; i ++ ) {
		sum[i] = sum[ i - 1 ] + (flag[i] == 0);
	}
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	init();
	int T = read<int>();
	while( T -- ) {
		ll n, res = 0; int k;
		n = read<ll>(); k = read<int>(); 
		if( k <= 8 ) {
			for( int i = 1; i < full_pow(k); i ++ ) {
				res += ( p[i]? 1: -1 ) * ( n / mul[i] );
			}
			printf( "%lld\n", n - res );
		} 
		else {
			for( int i = 0; i < full_pow( k - 8 ); i ++ ) {
				ll tmp = n / mul2[i];
				ll cur = ( tmp / base ) * sum[ base - 1 ] + sum[ tmp % base ];
				res += ( p[i]? -1: 1 ) * cur;
			}
			printf( "%lld\n", res );
		}
	}
}
