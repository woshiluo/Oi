/*
 * c.cpp 2024-10-02
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
constexpr T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
constexpr T Min( T a, T b ) { return a < b? a: b; }
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
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ( ch - '0' );
	return sum * fl;
}
template <class T> 
constexpr T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 1e4 + 1e3;
const int K = 31;

int a[N];

bool pre[N][K][2], suf[N][K][2];

constexpr i32 lowbit( ci32 cur ) { return cur & ( -cur ); }
constexpr i32 hibit( i32 cur ) {
	while( cur != lowbit(cur) ) 
		cur -= lowbit(cur);
	return cur;
}

constexpr i32 get_log( i32 cur ) {
	int res = -1;
	while( cur ) {
		cur >>= 1;
		res ++;
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif


	ci32 n = read<i32>();

	for( int i = 1; i <= n; i ++ ) 
		a[i] = read<i32>();
	
	for( int k = 0; k < K; k ++ ) 
		for( int p = 0; p < 2; p ++ ) 
			pre[1][k][p] = suf[n][k][p] = 1;
	for( int i = 2; i <= n; i ++ ) {
		for( int k = 0; k < K; k ++ ) 
			for( int p = 0; p < 2; p ++ ) 
				pre[i][k][p] = pre[ i - 1 ][k][p];
		if( a[i] != a[ i - 1 ] ) {
			ci32 max_valid = get_log( hibit( a[i] ^ a[ i - 1 ] ) );
			if( a[i] > a[ i - 1 ] )
				pre[i][ max_valid ][1] = 0;
			else 
				pre[i][ max_valid ][0] = 0;
		}
	}
	for( int i = n - 1; i >= 1; i -- ) {
		for( int k = 0; k < K; k ++ ) 
			for( int p = 0; p < 2; p ++ ) 
				suf[i][k][p] = suf[ i + 1 ][k][p];
		if( a[i] != a[ i + 1 ] ) {
			ci32 max_valid = get_log( hibit( a[i] ^ a[ i + 1 ] ) );
			if( a[i] > a[ i + 1 ] )
				suf[i][ max_valid ][1] = 0;
			else 
				suf[i][ max_valid ][0] = 0;
		}
	}

	for( int i = 2; i < n; i ++ ) {
		i32 res = 0;
		bool flag = true;
		for( int k = 0; k < K; k ++ ) {
			if( pre[i][k][0] && suf[i][k][0] ) {
				continue;
			}
			else if( pre[i][k][1] && suf[i][k][1] ) {
				res |= 1 << k;
			}
			else {
				flag = false;
				break;
			}
		}
		if( flag ) {
			printf( "%d\n", res );
			return 0;
		}
	}
}
