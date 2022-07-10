/*
 * d2.cpp
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

const int N = 2e7 + 10;

int pool[N]; 
ll f[N];

std::vector<int> primes;
bool is_prime[N];

void pre() {
	memset( is_prime, true, sizeof(is_prime) );
	for( int i = 2; i < N; i ++ ) {
		if( is_prime[i] ) 
			primes.push_back(i);
		for( auto &x: primes ) {
			if( 1LL * x * i >= N ) 
				break;
			is_prime[ x * i ] = false;
			if( i % x == 0 ) 
				break;
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "d2.in", "r", stdin );
	freopen( "d2.out", "w", stdout );
#endif
	pre();

	cint n = read<int>();
	for( int i = 1; i <= n; i ++ ) 
		pool[ read<int>() ] ++;
	for( auto &p: primes ) {
		for( int j = ( N - 1 ) / p; j >= 1; j -- ) {
			pool[j] += pool[ j * p ];
		}
	}

	ll ans = 0;
	for( int i = N - 1; i >= 1; i -- ) {
		chk_Max( f[i], 1LL * pool[i] * i );
		for( auto &p: primes ) {
			if( 1LL * i * p >= N ) 
				break;
			cint nxt = i * p;
			chk_Max( f[i], f[nxt] + 1LL * ( pool[i] - pool[nxt] ) * i );
		}
		chk_Max( ans, f[i] );
	}

	printf( "%lld\n", ans );
}
