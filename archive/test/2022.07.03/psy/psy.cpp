/*
 * tmp.cpp
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
#include <unordered_map>

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

const int mod = 1e9 + 7;

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

const int N = 1e7 + 5;

std::vector<int> primes;
bool is_prime[N];
ModInt mu[N], s[N];

void pre() {
	memset( is_prime, true, sizeof(is_prime) );
	mu[1] = 1;
	for( int i = 2; i < N; i ++ ) {
		if( is_prime[i] ) {
			primes.push_back(i);
			mu[i] = -1;
		}
		for( auto &prime: primes ) {
			if( 1LL * prime * i >= N ) 
				break;
			is_prime[ prime * i ] = false;
			mu[ prime * i ] = (ModInt)0 - mu[i];
			if( i % prime == 0 ) {
				mu[ prime * i ] = 0;
				break;
			}
		}
	}
	for( int i = 1; i < N; i ++ ) 
		s[i] = s[ i - 1 ] + ( mu[i] * i );
}

ModInt sum( const ll left, const ll rig ) { return (ModInt)( left + rig ) * ( rig - left + 1 ) * 500000004; }

std::unordered_map<ll, ModInt> mp;

ModInt S( const ll cur ) {
	if( cur < N ) 
		return s[cur];
	if( mp.count(cur) ) 
		return mp[cur];
	ModInt res = 1;
	for( ll left = 2, rig = 2; left <= cur; left = rig + 1 ) {
		rig = cur / ( cur / left );
		res -= sum( left, rig ) * S( cur / left );
	}
	return mp[cur] = res;
}

ModInt g( const ll cur ) {
	return ( pow( (ModInt) 10, ( cur + 1 ) % ( mod - 1 ) ) * cur -
			( pow( (ModInt) 10, ( cur + 1 )  % ( mod - 1 ) ) - 10 ) * 111111112 ) * 111111112;
}

int main() {
	freopen( "psy.in", "r", stdin );
	freopen( "psy.out", "w", stdout );
	
	pre();

	const ll n = read<ll>();

	ModInt res = 0;
	for( ll left = 1, rig = 1; left <= n; left = rig + 1 ) {
		rig = ( n / ( n / left ) );
		res += ( S(rig) - S( left - 1 ) ) * g( n / left );
	}

	res.output();

	fclose( stdin );
	fclose( stdout );
	return 0;
}
