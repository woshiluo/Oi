/*
 * d.cpp 2024-03-10
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

const int M = 256;
const int mod = 998244353;

int kk;

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

const ModInt G = 3;
struct Poly {/*{{{*/
	bool is_dot;
	ModInt a[M];
	Poly() { 
		is_dot = false; 
		memset( a, 0, sizeof(a) );
	}

	void change() {/*{{{*/
		is_dot ^= 1;
		static int r[M];
		for( int i = 0; i < M; i ++ ) {
			r[i] = r[ i >> 1 ] >> 1;
			if( i & 1 ) 
				r[i] |= (M >> 1);
		}
		for( int i = 0; i < M; i ++ ) 
			if( r[i] < i ) 
				std::swap( a[i], a[ r[i] ] );
	}/*}}}*/

	void ntt( bool on ) {/*{{{*/
		if( on != is_dot )
			return ;
		this -> change();

		for( int h = 2; h <= M; h <<= 1 ) {
			int k = ( h >> 1 );
			ModInt wn = pow( G, ( mod - 1 ) / h );
			if( on ) 
				wn = (ModInt)1 / wn;
			for( int i = 0; i < M; i += h ) {
				ModInt w = 1;
				for( int j = 0; j < k; j ++ ) {
					const int cur = i + j, nxt = i + j + k;
					const ModInt u = a[cur],
						v = w * a[nxt];

					a[cur] = u + v;
					a[nxt] = u - v;

					w *= wn;
				}
			}
		}

		if( on ) {
			for( int i = 0; i < M; i ++ ) 
				a[i] /= M;
		}
	}/*}}}*/

	Poly operator* ( Poly &b ) {/*{{{*/
		Poly res;
		this -> ntt(false); b.ntt(false);

		for( int i = 0; i < M; i ++ ) {
			res.a[i] = a[i] * b.a[i];
		}
		res.is_dot = true;

		res.ntt(true);

		for( int i = kk; i < M; i ++ ) {
			res.a[ i % kk ] += res.a[i];
			res.a[i] = 0;
		}

		return res;
	}/*}}}*/

	void output() {
		this -> ntt(true);
		for( int i = 0; i < 20; i ++ ) 
			a[i].output( ' ' );
		printf( "\n" );
	}
};/*}}}*/

const int N = 2e5 + 1e4;

i32 a[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 n = read<i32>();
	kk = read<i32>();
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}

	i32 q = read<i32>();

	while( q -- ) {
		ci32 l = read<i32>() + 1;
		ci32 r = read<i32>();

		Poly res;
		res.a[ a[ l - 1 ] % kk ] += 1;
		res.a[0] += 1;
		for( int i = l; i <= r; i ++ ) {
			Poly b;
			b.a[ a[i] % kk ] += 1;
			b.a[0] += 1;
			res = res * b;
		}

		res.a[0].output();
	}
}
