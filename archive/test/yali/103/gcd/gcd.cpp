/*
 * gcd.cpp
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

#include <random>
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

std::random_device rd;
std::mt19937 rnd(rd());

const int N = 1e6 + 10;

int n;
ll ans, a[N];
bool is_prime[N];
std::vector<int> prime_list;

void check( int cur ) {
	ll res = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( a[i] >= cur ) {
			res += Min( ( a[i] % cur ), cur - ( a[i] % cur ) );
		}
		else 
			res += ( cur - a[i] );
	}
	chk_Min( ans, res );
}

void try_a( ll cur ) {
	for( auto prime: prime_list ) {
		if( cur % prime == 0 ) {
			check(prime);
		}
	}
}

void init() {
	for( int i = 2; i < N; i ++ ) {
		is_prime[i] = true;
	}
	for( int i = 2; i < N; i ++ ) {
		if( is_prime[i] ) {
			prime_list.push_back(i);
		}
		for( auto prime: prime_list ) {
			ll cur = prime * i;
			if( cur >= N ) 
				break;
			is_prime[cur] = false;
			if( i % prime == 0 ) 
				break;
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "gcd.in", "r", stdin );
	freopen( "gcd.out", "w", stdout );
#endif
	init();
	n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<ll>();
	}

	ans = n;
	for( int _ = 1; _ <= 20; _ ++ ) {
		int pos = ( ( rnd() % n ) + 1 );
		try_a( a[pos] - 1 );
		try_a( a[pos] );
		try_a( a[pos] + 1 );
	}

	printf( "%lld\n", ans );
}
