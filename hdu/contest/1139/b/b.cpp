/*
 * b.cpp 2024-07-16
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

const int mod = 998244353;

template <class T>/*{{{*/
inline T inv( T a ) { return pow( a, mod - 2 ); }


struct ModInt {
	int cur;
	ModInt( int _cur = 0 ) { cur = ( _cur + mod ) % mod; }

	ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	ModInt operator- ( const ModInt &b ) const { return ( ( (  cur - b.cur ) % mod ) + mod )  % mod; }
	ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * inv(b).cur ) % mod; }

	void operator+= ( const ModInt &b ) { *this = (*this) + b; }
	void operator-= ( const ModInt &b ) { *this = (*this) - b; }
	void operator*= ( const ModInt &b ) { *this = (*this) * b; }
	void operator/= ( const ModInt &b ) { *this = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

const ModInt G = 3;

struct Poly {// {{{
	std::vector<ModInt> a;

	Poly( int n ) { a.resize(n); }
	void change() {
		int len = a.size();
		std::vector<int> r; r.resize(len);

		for( int i = 0; i < len; i ++ ) {
			r[i] = ( r[ i >> 1 ] >> 1 );
			if( i & 1 ) 
				r[i] |= ( len >> 1 );
		}

		for( int i = 0; i < len; i ++ ) {
			if( r[i] < i )  
				std::swap( a[i], a[ r[i] ] );
		}
	}

	void ntt( bool on = false ) {
		this -> change();

		int len = a.size();
		for( int h = 2; h <= len; h <<= 1 ) {
			int k = ( h >> 1 );
			ModInt wi = pow( G, ( ( mod - 1 ) / h ) );
			if( on ) 
				wi = (ModInt)1 / wi;
			for( int i = 0; i < len; i += h ) {
				ModInt w = 1;
				for( int j = 0; j < k; j ++ ) {
					const int cur = i + j, nxt = i + j + k;
					const ModInt u = a[cur], v = w * a[nxt];
					a[cur] = u + v;

				}
			}
		}

		if( on ) {
			for( auto &x: a ) {
				x /= len;
			}
		}
	}

	void output() {
#ifdef DEBUG
		for( auto &x: a ) {
			x.output( ' ' );
		}
		printf( "\n" );
#endif
	}
};// }}}

// d_j = \sum c_{i+j} c{i}
// p_i = c_{n-i}
// d_j = \sum c_{i+j} p{i}
// n - i + i  + j = n + j

const int N = 1e6 + 5;

Poly c(N), p(N);

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 t = read<i32>();

	std::vector<i32> a( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<i32>();
		c.a[ a[i] ] += 1;
		p.a[ N - a[i] ] += 1;
	}

	c.ntt();
	p.ntt();
	Poly q



}
