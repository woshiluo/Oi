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

const int magic = 223092870;

const int X = 4;
const int K = 9;
const int prime[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };

int query( int a, int b ) {
	printf( "? %d %d\n", a, b );
	fflush(stdout);
//	return std::__gcd( X + a, X + b );
	int res = 0;
	scanf( "%d", &res );
	return res;
}

void answer( const int res ) {
	printf( "! %d\n", res );
	fflush(stdout);
}

bool check( const int p ) {
	if( p > (int)(1e9) )
		return false;
	if( p == (int)(1e9) )
		return query( 1e9, 2e9 ) == (int)(1e9);
	const int k = query( (int)(1e9) - p, (int)(2e9) - p );
	return k == (int)(1e9);
}

int main() {
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		std::vector<int> a(K);
		std::vector<ll> c(K);
		for( int i = 1; i <= 23; i ++ ) {
			int p = query( magic * 2 + i, magic * 3 + i );
			for( int j = 0; j < K; j ++ ) {
				if( p % prime[j] == 0 && prime[j] - i >= 0 ) 
					a[j] = prime[j] - i;
			}
		}
		for( int i = 0; i < K; i ++ ) {
			const int m = magic / prime[i];
			const int mod = prime[i];
			int inv = 1;
			for( int j = 0; j < prime[i] - 2; j ++ ) {
				inv = ( 1LL * inv * m ) % mod;
			}
			c[i] = 1LL * m * inv;
		}
		int x = 0;
		for( int i = 0; i < K; i ++ ) {
			const int mul = ( 1LL * a[i] * c[i] ) % magic;
			x = ( x + mul ) % magic;
		}
		int res = 0;
		for( int i = 0; i <= 5; i ++ ) {
			if( check( x + magic * i ) ) {
				res = x + magic * i;
				break;
			}
		}
		answer(res);
	}
}
