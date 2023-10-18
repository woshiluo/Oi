/*
 * g.cpp 2023-09-24
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

constexpr static int full_pow( cint cur ) { return 1 << cur; }
constexpr static bool chk_pos( cint cur, cint pos ) { return cur & full_pow(pos); }
ModInt fact( cint cur ) {
	ModInt res = 1;
	for( int i = 2; i <= cur; i ++ ) 
		res *= i;
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();


	std::vector<int> r(m), b(m);
	std::vector<ModInt> f(full_pow(n)), g(full_pow(n));

	for( auto &x: r ) 
		x = read<int>() - 1;
	for( auto &x: b ) 
		x = read<int>() - 1;

	ModInt ans = 0;
	for( int sta = 1; sta < full_pow(n); sta ++ ) {
		int res = 0;
		for( int i = 0; i < m; i ++ ) {
			if( chk_pos( sta, r[i] ) && chk_pos( sta, b[i] ) ) 
				res ++;
		}
		if( res == 0 ) 
			continue;
		f[sta] = fact(res);
		g[sta] = f[sta];
		for( int sub_sta = ( sta - 1 ) & sta; sub_sta > ( sta - sub_sta ); sub_sta = ( sub_sta - 1 ) & sta ) {
			g[sta] -= g[sub_sta] * f[ sta - sub_sta ];
		}
		ans += g[sta] * fact( m - res );
	}

	ans /= fact(m);
	ans.output();
}
