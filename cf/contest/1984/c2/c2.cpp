/*
 * c2.cpp 2024-06-11
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

const i32 mod = 998244353;

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

struct ModInt {/*{{{*/
	int cur;
	ModInt( i32 _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }
	ModInt( i64 _cur ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( (i64)cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( (i64)cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

const int N = 2e5 + 1e4;

template <class T>
T aabs( T cur ) { return cur < 0? -cur: cur; }

int main() {
#ifdef woshiluo
	freopen( "c2.in", "r", stdin );
	freopen( "c2.out", "w", stdout );
#endif

	
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		i64 min = 0, max = 0;
		static ModInt f[N][2];
		f[0][0] = 1; f[0][1] = 1;
		for( int i = 1; i <= n; i ++ ) {
			f[i][0] = f[i][1] = 0;
			ci32 x = read<i32>();
			ci64 min_1 = min + x;
			ci64 min_2 = aabs( min + x );
			ci64 max_1 = max + x;
			ci64 max_2 = aabs( max + x );

			ci64 target_min = Min( Min( min_1, min_2 ), Min( max_1, max_2 ) );
			ci64 target_max = Max( Max( min_1, min_2 ), Max( max_1, max_2 ) );

			if( min_1 == target_min ) {
				f[i][0] += f[ i - 1 ][0];
			}
			if( min_2 == target_min ) {
				f[i][0] += f[ i - 1 ][0];
			}
			if( min != max && max_1 == target_min ) {
				f[i][0] += f[ i - 1 ][1];
			}
			if( min != max && max_2 == target_min ) {
				f[i][0] += f[ i - 1 ][1];
			}

			if( min_1 == target_max ) {
				f[i][1] += f[ i - 1 ][0];
			}
			if( min_2 == target_max ) {
				f[i][1] += f[ i - 1 ][0];
			}
			if( min != max &&  max_2 == target_max ) {
				f[i][1] += f[ i - 1 ][1];
			}
			if( min != max && max_1 == target_max ) {
				f[i][1] += f[ i - 1 ][1];
			}

			min = target_min;
			max = target_max;
		}
		f[n][1].output();
	}
}
