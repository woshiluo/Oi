#pragma GCC optimize("Ofast,unroll-loops")
/*
 * d.cpp 2024-04-12
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

struct ModInt {/*{{{*/
	int cur;
	ModInt( i32 _cur = 0 ) { cur = _cur; }

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


const int N = 10005;

ModInt f[2][N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	
	ci32 n = read<i32>();
	std::vector<i32> a(n);
	for( auto &x: a )
		x = read<i32>();
	std::sort( a.begin(), a.end() );
	ModInt res_0 = 0, res_1 = 0, p0 = 1, p1 = 0;
	for( int i = 0; i < n; i ++ ) {
		ModInt pre_0 = res_0, pre_1 = res_1, o0 = p0, o1 = p1;
		if( a[i] & 1 ) {
			res_1 += pre_0 + o0 * a[i];
			res_0 += pre_1 + o1 * a[i];
			p0 += o1;
			p1 += o0;
		}
		else {
			res_0 += pre_0 + o0 * a[i];
			res_1 += pre_1 + o1 * a[i];
			p0 += o0;
			p1 += o1;
		}
	}

	ModInt res = res_0 / 2 + ( res_1 + p1 ) / 2;

	int cur = 0, la = 1;
	f[la][0] = 1;
	for( int i = 0; i < n; i ++, cur ^= 1, la ^= 1) {
		for( int j = 0; j < N; j ++ ) {
			f[cur][j] = f[la][j];
			if( j - a[i] >= 0 ) {
				f[cur][j] += f[la][ j - a[i] ];
				res += f[la][j - a[i]] * a[i];
				res -= f[la][j - a[i]] * Min( a[i], ( j >> 1 ) + ( j & 1 ) );
			}
		}
	}

	res.output();

}
