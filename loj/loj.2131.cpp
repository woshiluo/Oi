/*
 * loj.2131.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * g
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cmath>
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
	for (; !isdigit(ch); ch = getchar())
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

inline int full_pow( int k ) { return 1 << k; }
inline bool has( int p, int i ) {
	return p & ( 1 << i );
}

int mod;

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

const int N = 510;
const int K = 10;
const int P = full_pow(K);

bool is_prime[N];
std::vector<int> prime;

void get_prime() {
	for( int i = 2; i < N; i ++ ) {
		bool flag = true;
		for( int j = 2; j <= std::sqrt(i); j ++ ) {
			if( i % j == 0 ) {
				flag = false;
				break;
			}
		}
		if( flag ) {
			is_prime[i] = true;
			prime.push_back(i);
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "loj.2131.in", "r", stdin );
	freopen( "loj.2131.out", "w", stdout );
#endif
	int n = read<int>(); mod = read<int>();
	get_prime();

	ModInt f[P];
	for( int i = 0; i < P; i ++ ) {
		int cnt = 0;
		for( int j = 2; j <= n; j ++ ) {
			bool flag = false;
			for( int k = 0; k < K; k ++ ) {
				if( has( i, k ) && j % prime[k] == 0 ) 
					flag = true;
			}
			cnt += flag;
		}
		ModInt res = pow( 2, cnt );
		for( int j = 0; j < P; j ++ ) {
			if( ( i & j ) == j ) 
				res -= f[j];
		}
		f[i] = res;
	}

	int cnt = 0;
	for( auto a: prime ) {
		if( a > n ) 
			break;
		cnt += ( a > 30 );
	}

	ModInt ans = 0;
	for( int i = 0; i < P; i ++ ) {
		for( int j = 0; j < P; j ++ ) {
			if( i & j ) 
				continue;
			if( f[i].cur == 0 || f[ ( i | j ) ^ ( P - 1 ) ].cur == 0 ) 
				continue;
			ans += ( f[i] * f[ ( i | j ) ^ ( P - 1 ) ] * pow( (ModInt)3, cnt ) );
		}
	}
	ans.output();
}
