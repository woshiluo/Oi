/*
 * a.cpp 2024-03-15
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

const int MAX = 1024;

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

//ModInt f[2][MAX];
//bool vis[2][MAX];

int print( ci32 n ) {
	if( n == 0 ) {
//		printf( "0" );
		return 0;
	}
	else {
		int res = print( n >> 1 ) + 1;
//		printf( "%d", n & 1 );
		return res;
	}
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
//		memset( f, 0, sizeof(f) );
//		int cur = 0, la = 1;
//		f[la][0] = 1;
//		vis[la][0] = true;
//		for( int i = 0; i <= n; i ++, cur ^= 1, la ^= 1) {
//			for( int j = 0; j < MAX; j ++ ) {
//				f[cur][j] = 0;
//				vis[cur][j] = 0;
//				if( vis[la][j] ) {
//					vis[cur][j] = true;
//					f[cur][j] += f[la][j];
//				}
//				if( vis[la][ j ^ i ] ) {
//					vis[cur][j] = true;
//					f[cur][j] += f[la][j ^ i];
//				}
//			}
//		}
		int count = print( n );
//		( f[la][0] - 1 ).output();
		( pow( (ModInt)(2), n - count + 1 ) - 1 ).output();
//		printf( "%lld\n", pow( , n - count + 1 ) - 1 );
	}
	
}
