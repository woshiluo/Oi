/*
 * d.cpp 2024-03-03
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


const int N = 2e5 + 1e4;
const int mod = 998244353;

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

char str[N];
ModInt f[N][2][2];

ModInt dfs( ci32 depth, const bool max_x, const bool max_y ) {
	if( depth == 0 ) 
		return 1;
	if( f[depth][max_x][max_y].cur != 0 ) 
		return f[depth][max_x][max_y];
	f[depth][max_x][max_y] = 0;
	for( int i = 0; i <= ( max_x? str[depth]: 1 ); i ++ ) {
		for( int j = 0; j <= ( max_y? str[depth]: 1 ); j ++ ) {
			if( ( i | j ) == ( i ^ j ) )
				f[depth][max_x][max_y] += dfs( depth - 1, max_x && ( i == str[depth] ), max_y && ( j == str[depth] ) );
		}
	}
	return f[depth][max_x][max_y];
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	scanf( "%s", str + 1 );
	int res = 0;
	for( int i = 0; i <= 6; i ++ ) {
		for( int j = 0; j <= 6; j ++ ) {
			if( ( i | j ) == ( i ^ j ) ) {
				printf( "%d %d\n", i, j );
				res ++;
			}
		}
	}
	printf( "%d\n",  res );
	ci32 n = strlen( str + 1 );
	std::reverse( str + 1, str + n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		str[i] -= '0';
	}
	dfs( n, 1, 1 ).output();
}
