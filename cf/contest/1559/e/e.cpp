/*
 * e.cpp
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

#include <bitset>
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

const int mod = 998244353;
const int N = 60;
const int M = 1e5 + 1e4;

struct ModInt {/*{{{*/
	int cur;
	ModInt( int _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

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

int n, m;
int left[N], rig[N], mu[M];

ModInt solve( int k ) {/*{{{*/
	int tm = m / k;
	static ModInt f[M], sum[M];
	auto query = []( int l, int r ) { 
		if( r < 0 ) 
			return (ModInt)0;
		if( l < 0 ) 
			l = 0;
		if( l == 0 ) 
			return sum[r];
		return sum[r] - sum[ l - 1 ]; 
	};
	for( int i = 0; i <= tm; i ++ ) {
		sum[i] = 1;
	}
	for( int i = 1; i <= n; i ++ ) {
		int l = left[i], r = rig[i];
		l = ( l / k ) + ( l % k != 0 ), r = r / k;
		if( l > r ) 
			return 0;
		for( int j = 0; j <= tm; j ++ ) {
			f[j] = query( j - r, j - l );
		}
		sum[0] = f[0];
		for( int j = 1; j <= tm; j ++ ) {
			sum[j] = sum[ j - 1 ] + f[j];
		}
	}
	ModInt res = 0;
	for( int i = 0; i <= tm; i ++ ) {
		res += f[i];
	}
	return res;
}/*}}}*/

std::vector<int> prime_list;
void get_mu() {
	std::bitset<M> is_prime;
	is_prime.set();
	mu[1] = 1;
	for( int i = 2; i <= m; i ++ ) {
		if( is_prime[i] ) {
			prime_list.push_back(i);
			mu[i] = -1;
		}
		for( auto prime: prime_list ) {
			if( 1LL * i * prime > m ) 
				break;
			int nxt = i * prime;
			is_prime[nxt] = false;
			if( i % prime == 0 ) {
				mu[nxt] = 0;
				break;
			}
			mu[nxt] = -mu[i];
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	n = read<int>(); m = read<int>();
	get_mu();
	for( int i = 1; i <= n; i ++ ) {
		left[i] = read<int>(); rig[i] = read<int>();
	}
	ModInt ans = 0;
	for( int i = 1; i <= m; i ++ ) {
		ans += solve(i) * mu[i];
	}
	ans.output();
}
