/*
 * a.cpp
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

int mod;

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

ll gcd( ll a, ll b ) { return b? gcd( b, a % b ): a; }
ll lcm( ll a, ll b ) { return a / gcd( a, b ) * b; }

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int T = read<int>(); 
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();
		mod = read<int>();
		if( mod == 2 || mod == 5 ) {
			printf( "0\n" );
			continue;
		}

		if( mod == 3 ) {
			printf( "%lld\n", 1LL * ( n / 3 ) * m );
			continue;
		}
		int p = mod - 1;
		// Minium p
		{ 
			int tp = p;
			for( int i = 1; 1LL * i * i <= tp; i ++ ) {
				if( tp % i == 0 ) {
					if( pow( (ModInt)10, i ).cur == 1) {
						chk_Min( p, i );
					}
					if( pow( (ModInt)10, tp / i ).cur == 1) {
						chk_Min( p, tp / i );
					}
				}
			}
		}

		int max_k = 0;
		std::vector<int> pp, pa;
		{
			int tp = p;
			for( int i = 2; 1LL * i * i <= tp; i ++ ) {
				if( tp % i == 0 ) {
					int cnt = 0;
					while( tp % i == 0 ) {
						cnt ++;
						tp /= i;
					}
					pp.push_back(i);
					pa.push_back(cnt);
					chk_Max( max_k, cnt );
				}
			}
			if( tp != 1 ) {
				pp.push_back(tp);
				pa.push_back(1);
				chk_Max( max_k, 1 );
			}
		}

		cint size = pa.size();
		ll ans = 0;
		for( int k = 1; k < max_k; k ++ ) {
			int cur = 1;
			for( int i = 0; i < size; i ++ ) {
				cur *= pow( pp[i], ( pa[i] / k ) + ( pa[i] % k != 0 ) );
			}
			if( k <= m )
				ans += 1LL * ( n / cur );
		}
		{
			int cur = 1;
			for( int i = 0; i < size; i ++ ) {
				cur *= pow( pp[i], 1 );
			}
			ans += 1LL * ( n / cur ) * Max( m - max_k + 1, 0 );
		}

		printf( "%lld\n", ans );
	}
}

