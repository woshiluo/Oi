/*
 * train.cpp
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

#include <sys/types.h>
#include <utility>
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

const int N = 50;

ll mod = 2;
ll a[N];

struct ModInt {/*{{{*/
	ll cur;
	ModInt( ll _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
//	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
//	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
//	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
//	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
//	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
//	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%lld%c", cur, end ); }
};/*}}}*/

ll full_pow( const ll cur ) { return 1LL << cur; }
bool chk_pos( const ll cur, const ll k ) { return cur & full_pow(k); }
std::vector<std::pair<ll, int>> list[2];

int main() {
#ifdef woshiluo
	freopen( "train.in", "r", stdin );
	freopen( "train.out", "w", stdout );
#endif

	cint n = read<int>();
	mod = read<ll>();

	if( n == 1 ) {
		printf( "IMPOSSIBLE\n" );
		return 0;
	}

	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<ll>();
	}

	cint n1 = ( n >> 1 );
	cint n2 = n - n1;
	list[0].resize( 1 << n1 );
	list[1].resize( 1 << n2 );
	{/*{{{*/
		for( int st = 0; st < full_pow(n1); st ++ ) {
			ll res = 0;
			for( int j = 0; j < n1; j ++ ) {
				if( chk_pos( st, j ) ) 
					res += a[ j + 1 ];
			}
			list[0][st] = std::make_pair(res % mod, st);
		}
		for( int st = 0; st < full_pow(n2); st ++ ) {
			ll res = 0;
			for( int j = 0; j < n2; j ++ ) {
				if( chk_pos( st, j ) ) 
					res += a[ n1 + j + 1 ];
			}
			list[1][st] = std::make_pair( res % mod , st);
		}
	}/*}}}*/

	std::sort( list[0].begin(), list[0].end() );
	std::sort( list[1].begin(), list[1].end() );

	auto check = []( ll left, ll rig ) {
		ll res = 0;
		cint size = list[1].size();

		int p0 = size - 1, p1 = size - 1;
		for( auto x: list[0] ) {
			while( p0 - 1 >= 0 && list[1][ p0 - 1 ].first + x.first >= left ) 
				p0 --;
			while( p1 - 1 >= 0 && list[1][p1].first + x.first > rig ) 
				p1 --;

			const ll val = list[1][p0].first + x.first;
			if( left <= val && val <= rig )
				res += ( p1 - p0 + 1 );
		}

		left += mod, rig += mod;
		p0 = p1 = size - 1;
		for( auto x: list[0] ) {
			while( p0 - 1 >= 0 && list[1][ p0 - 1 ].first + x.first >= left ) 
				p0 --;
			while( p1 - 1 >= 0 && list[1][p1].first + x.first > rig ) 
				p1 --;

			const ll val = list[1][p0].first + x.first;
			if( left <= val && val <= rig )
				res += ( p1 - p0 + 1 );
		}

		return res > ( rig - left + 1 );
	};

	ll left = 0, rig = mod - 1;
	while( left < rig ) {
		const ll mid = ( left + rig ) >> 1;
		if( check( left, mid ) ) 
			rig = mid;
		else 
			left = mid + 1;
	}

	{
		std::vector<ll> masks;
		cint size = list[1].size();

		int p0 = size - 1, p1 = size - 1;
		for( auto &x: list[0] ) {
			while( p0 - 1 >= 0 && list[1][ p0 - 1 ].first + x.first >= left ) 
				p0 --;
			while( p1 - 1 >= 0 && list[1][p1].first + x.first > rig ) 
				p1 --;

			const ll val = list[1][p0].first + x.first;
			if( left <= val && val <= rig ) {
				masks.push_back( (ll)x.second + ( (ll)list[1][p0].second << n1 ) );
				if( p1 > p0 ) {
					masks.push_back( (ll)x.second + ( (ll)list[1][p1].second << n1 ) );
				}
			}
		}

		p0 = p1 = size - 1;
		for( auto &x: list[0] ) {
			while( p0 - 1 >= 0 && list[1][ p0 - 1 ].first + x.first >= left + mod ) 
				p0 --;
			while( p1 - 1 >= 0 && list[1][p1].first + x.first > rig + mod ) 
				p1 --;

			const ll val = list[1][p0].first + x.first;
			if( left + mod <= val && val <= rig + mod ) {
				masks.push_back( (ll)x.second + ( (ll)list[1][p0].second << n1 ) );
				if( p1 > p0 ) {
					masks.push_back( (ll)x.second + ( (ll)list[1][p1].second << n1 ) );
				}
			}
		}

		ll m1 = masks[0], m2 = masks[1];
		const ll diff = m1 & m2;
		m1 ^= diff, m2 ^= diff;

		for( int i = 0; i < n; i ++ ) {
			if( chk_pos( m1, i ) ) 
				printf( "1 " );
			else if( chk_pos( m2, i ) ) 
				printf( "-1 " );
			else
				printf( "0 " );
		}
	}
}
