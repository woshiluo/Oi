/*
 * 9.cpp 2024-08-04
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cinttypes>

#include <map>
#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
constexpr T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
constexpr T Min( T a, T b ) { return a < b? a: b; }
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
constexpr T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 1e7;

std::vector<i32> primes;
i64 mu[N], muk[N];
bool not_prime[N];
void pre() {
	mu[1] = 1;
	not_prime[1] = true;
	for( int i = 2; i < N; i ++ ) {
		if( !not_prime[i] ) {
			primes.push_back(i);
			mu[i] = -1;
		}
		for( auto &p: primes ) {
			if( 1LL * i * p >= N )
				break;
			not_prime[ i * p ] = true;
			mu[ i * p ] = -mu[i];
			if( i % p == 0 ) {
				mu[ i * p ] = 0;
				break;
			}
		}
	}
	for( int i = 1; i < N; i ++ ) {
		muk[i] = muk[ i - 1 ] + mu[i] * i;
		mu[i] += mu[ i - 1 ];
	}
}

std::map<i32, i64> mp_sum_mu, mp_sum_muk;


i64 sum_mu( i32 x ) {
	if( x < N ) 
		return mu[x];
	if( mp_sum_mu.count(x) ) 
		return mp_sum_mu[x];

	const static auto len = []( ci32 l, ci32 r ) { return r - l + 1; };

	i64 res = 1;
	for( int l = 2, r = 1; l <= x; l = r + 1 ) {
		r = Min( x, x / ( x / l ) );
		res -= (i64)len( l, r ) * sum_mu( x / l );
	}

	mp_sum_mu[x] = res;
	return res;
}

i64 sum_muk( i32 x ) {
	if( x < N ) 
		return muk[x];
	if( mp_sum_muk.count(x) ) 
		return mp_sum_muk[x];

	const static auto len = []( ci32 l, ci32 r ) { return r - l + 1; };
	const static auto c2 = []( ci32 l, ci32 r ) { return (i64)len( l, r ) * ( l + r ) / 2LL; };

	i64 res = 1;
	for( int l = 2, r = 1; l <= x; l = r + 1 ) {
		r = Min( x, x / ( x / l ) );
		res -= (i64)c2( l, r ) * sum_muk( x / l );
	}

	mp_sum_muk[x] = res;
	return res;
}

i64 query( ci32 n, ci32 a ) {
	i64 res = 0;
	for( int l = 1, r = 1; l <= a && l <= n; l = r + 1 ) {
		r = Min( n, a / ( a / l ) );
		res += (i64)(a / l) * ( sum_muk(r) - sum_muk( l - 1 ) );
	}
	return res;
}


int main() {
#ifdef woshiluo
	freopen( "9.in", "r", stdin );
	freopen( "9.out", "w", stdout );
#endif

	pre();

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 a = read<i32>();

		printf( "%" PRId64 "\n", a * sum_mu(n) - query(n, a) );
	}
	
}
