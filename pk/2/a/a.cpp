/*
 * a.cpp 2024-03-10
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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const i32 N = 1e7 + 10;
const i32 mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( i64 _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

i32 fact[N], ifac[N], p[N];

// choose m in n
i32 choose( ci32 n, ci32 m ) { 
	if( n < 0 || m < 0 )
		return 1;
	if( m == 0 ) 
		return 1;
	if( n < m ) 
		return 1;
	return ( ( ( 1LL * fact[n] * ifac[m] ) % mod ) *  ifac[ n - m ] ) % mod; 
}


int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	{
		fact[0] = 1;
		for( int i = 1; i < N; i ++ ) 
			fact[i] = ( 1LL * fact[ i - 1 ] * i ) % mod;
		ifac[ N - 1 ] = ((ModInt)1 / (ModInt)fact[ N - 1 ]).cur;
		for( int i = N - 2; i >= 0; i -- ) 
			ifac[i] = ( 1LL * ifac[ i + 1 ] * ( i + 1 ) ) % mod;
	}

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 k = read<i32>();
		i32 res = 0;

		p[0] = 0;
		ci32 max = n - k - 1;
		for( int l = 0; l <= max; l ++ ) {
			if( n - l - 1 < 0 )
				break;
			if( l == 0 && k != 0 ) 
				continue;
			p[l] = ( ( ( ( ( 1LL * choose( l + k - 1, l - 1 ) * fact[l + 1] ) % mod ) * fact[ n - l - 1 ] ) % mod ) * ( n - l ) ) % mod;
			if( l != 0 ) {
				p[l] += p[ l - 1 ];
				if( p[l] >= mod )
					p[l] -= mod;
			}
			res += p[l];
			if( res >= mod ) 
				res -= mod;
		}

		printf( "%d\n", res );
	}
}
