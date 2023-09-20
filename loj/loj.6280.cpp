/*
 * loj.6280.cpp
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
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

struct ModInt {/*{{{*/
	int cur, mod;
	ModInt( ll _cur = 0, ll _mod = 1 ) { mod = _mod, cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ModInt( ( cur + b.cur ) % mod, mod ); }
	inline ModInt operator- ( const ModInt &b ) const { return ModInt( ( ( ( cur - b.cur ) % mod ) + mod ) % mod, mod ); }
	inline ModInt operator* ( const ModInt &b ) const { return ModInt( ( 1LL * cur * b.cur ) % mod, mod ); }
	inline ModInt operator/ ( const ModInt &b ) const { return ModInt( ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod, mod ); }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

const int N = 5e4;
const int BLOCK_SIZE = 200;
// [1,BLOCK_SIZE] 

int get_block( cint cur ) { return ( cur - 1 ) / BLOCK_SIZE; }
bool is_border( cint cur ) { return ( cur % BLOCK_SIZE ) == 0 || ( cur % BLOCK_SIZE ) == 1; }

int main() {
#ifdef woshiluo
	freopen( "loj.6280.in", "r", stdin );
	freopen( "loj.6280.out", "w", stdout );
#endif
	static int a[N];
	static ll sum[N], tag[N];

	cint n = read<int>();

	for( int i = 1; i <= n; i ++ ) 
		a[i] = read<int>();

	for( int i = 1; i <= n; i ++ ) {
		sum[ get_block(i) ] += a[i];
	}

	for( int i = 1; i <= n; i ++ ) {
		cint op = read<int>();
	
		int l = read<int>();
		int r = read<int>();
		if( op == 0 ) {
			cint c = read<int>();
			while( l <= r && ( l - 1 ) % BLOCK_SIZE != 0 ) {
				a[l] += c;
				sum[ get_block(l) ] += c;
				l ++;
			}
			while( l <= r && r % BLOCK_SIZE != 0 ) {
				a[r] += c;
				sum[ get_block(r) ] += c;
				r --;
			}
			for( int j = get_block(l); l <= r && j <= get_block(r); j ++ ) {
				tag[j] += c;
			}
		}
		else {
			cint c = read<int>() + 1;
			ModInt res( 0, c );
			while( l <= r && ( l - 1 ) % BLOCK_SIZE != 0 ) {
				res += ModInt( a[l], c ) + ModInt( tag[ get_block(l) ], c );
				l ++;
			}
			while( l <= r && r % BLOCK_SIZE != 0 ) {
				res += ModInt( a[r], c ) + ModInt( tag[ get_block(r) ], c );
				r --;
			}
			for( int j = get_block(l); l <= r && j <= get_block(r); j ++ ) {
				res += ModInt( sum[j], c ) + ModInt( tag[j], c ) * ModInt( BLOCK_SIZE, c );
			}

			res.output();
		}
	}
}
