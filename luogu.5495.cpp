/*
 * luogu.5495.cpp
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
typedef unsigned int uint;

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

const int N = 2e7 + 1e4;

uint seed;/*{{{*/
inline uint getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}/*}}}*/

uint a[N], b[N];
std::vector<int> primes;
bool is_prime[N];

int main() {
	memset( is_prime, true, sizeof(is_prime) );
	cint n = read<int>();
	seed = read<uint>();

	for( int i = 1; i <= n; i ++ ) {
		a[i] = getnext();
		b[i] = a[i];
	}

	for( int i = 2; i <= n; i ++ ) {
		if( is_prime[i] ) 
			primes.push_back(i);
		for( auto &x: primes ) {
			if( 1LL * x * i > n ) 
				break;
			is_prime[ x * i ] = false;
			if( x % i == 0 ) 
				break;
		}
	}

	for( auto &x: primes ) {
		for( int i = 1; 1LL * i * x <= n; i ++ ) {
			a[ i * x ] += a[i];
		}
	}

	uint res = 0;
	for( int i = 1; i <= n; i ++ ) 
		res ^= a[i];

	printf( "%u\n", res );
}
