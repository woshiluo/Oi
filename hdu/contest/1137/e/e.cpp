/*
 * e.cpp 2024-07-11
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

const i32 mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( i32 _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }
	ModInt( long long _cur ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

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

const int N = 1e7 + 5;

ModInt fac[N], ifac[N];

void pre() {
	fac[0] = 1;
	for( int i = 1; i < N; i ++ ) 
		fac[i] = fac[ i - 1 ] * i;
	ifac[ N - 1 ] = (ModInt) 1 / fac[ N - 1 ];
	for( int i = N - 2; i >= 0; i -- ) 
		ifac[i] = ifac[ i + 1 ] * ( i + 1 );
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	pre();
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> list;
		ModInt base = 1;
		i32 count = 0;
		i32 tot = 0;
		for( int i = 1; i <= n; i ++ ) {
			static char op[3];
			scanf( "%s",  op);
			list.push_back( read<i32>() );
			base *= ifac[ list.back() ];
			count += list.back();
			tot += ( list.back() >> 1 );
		}
		base *= fac[ count ];
		if( tot == ( count >> 1 ) ) {
			ModInt base2 = fac[ count >> 1 ];
			for( auto &x: list ) {
				base2 *= ifac[ x >> 1 ];
			}
			ModInt p1 = ( base - base2 ) / 2;
			ModInt p2 = (ModInt)( ( count & 1 )? 1: 0 ) * base2;
			( ( p1 + p2 ) / base ).output();
		}
		else {
			( (ModInt) 1 / 2 ).output();
		}
	}
}
