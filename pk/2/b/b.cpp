/*
 * b.cpp 2024-03-10
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cmath>
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

const i32 MAXP = 11000;
const i32 mod = 998244353;

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

i32 nums[MAXP], num_cnt = 0;
i32 fac[MAXP], fp[MAXP], np[MAXP], facnt;
bool vis[MAXP];

inline int full_pow( ci32 cur ) { return 1 << cur; }
inline bool chk_pos( ci32 cur, ci32 pos ) { return ( cur >> pos ) & 1; }

signed main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();

		num_cnt = 0;
		facnt = 0;

		{/*{{{*/
			i32 cur = n;
			i32 sqrt = std::sqrt(n) + 10;
			for( int i = 2; i <= sqrt; i ++ ) {
				if( cur % i == 0 ) {
					facnt ++;
					fac[ facnt ] = i;
					fp[facnt] = 0;
					while( cur % i == 0 ) {
						fp[ facnt ] ++;
						cur /= i;
					}
				}
			}
			if( cur != 1 ) {
				facnt ++;
				fac[ facnt ] = cur;
				fp[ facnt ] = 1;
			}
		}/*}}}*/

		num_cnt ++;
		nums[ num_cnt ] = 1;
		for( int i = 1; i <= facnt; i ++ ) {
			int last_cnt = num_cnt;
			int cur = 1;
			for( int j = 1; j <= fp[i]; j ++ ) {
				cur *= fac[i];
				for( int k = 1; k <= last_cnt; k ++ ) {
					num_cnt ++;
					nums[ num_cnt ] = nums[k] * cur;
				}
			}
			np[i] = cur;
		}
		std::sort( nums + 1, nums + num_cnt + 1 );

		ModInt ans = 0;
		for( int mask = 0; mask < full_pow(facnt); mask ++ ) {
			int cnt = num_cnt;
			for( int i = 1; i <= facnt; i ++ ) {
				if( chk_pos( mask, i - 1 ) ) {
					for( int j = 1; j <= num_cnt; j ++ ) {
						if( !vis[j] && nums[j] % np[i] == 0 ) {
							vis[j] = true;
						}
					}
				}
			}
			for( int j = 1; j <= num_cnt; j ++ ) {
				cnt -= vis[j];
				vis[j] = false;
			}

			{
				i32 popcnt = __builtin_popcount(mask);
				ModInt res = pow( (ModInt)cnt, m );
				
				if( popcnt & 1 ) {
					ans = ans - res;
				}
				else {
					ans = ans + res;
				}
			}
		}
		ans.output();
	}
}
