/*
 * fft.cpp
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

#include <map>
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

const int mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( ll _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

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

std::map<ll, ModInt> mp;
ModInt solve( const ll left, const ll rig ) {
	if( mp.count( rig - left ) ) 
		return mp[ rig - left ];
	if( rig - left == 1 ) 
		return 1;

	const ll len = ( rig - left );
	ll p = 0, tmp = 1;
	for( ; tmp < len; tmp <<= 1LL, p ++ );
	ModInt res = (ModInt) tmp * p;
	const ll mid = ( 1LL << ( p - 1 ) );

	res += solve( left, left + mid );
	res += solve( left + mid, rig );

	mp[ rig - left ] = res;
	return res;
}

ll full_pow( ll cur ) { return 1LL << cur; }

int main() {
#ifdef woshiluo
	freopen( "fft.in", "r", stdin );
	freopen( "fft.out", "w", stdout );
#endif
	ll n = 0;

	cint k = read<int>(); 
	cint m = read<int>();

	for( int i = 1; i <= k; i ++ ) {
		cint l = read<int>();
		cint r = read<int>();
		for( int j = l; j <= r; j ++ ) {
			n += full_pow(j);
		}
	}

	for( int i = 1; i <= m; i ++ ) {
		cint op = read<int>();
		cint b = read<int>();
		n += full_pow(b) * ( ( op == 0 )? 1: -1 );
		solve( 0, n ).output();
	}
}
