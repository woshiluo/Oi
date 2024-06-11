/*
 * d.cpp 2024-03-01
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

const int N = 5e5 + 1e4;

template <class T>
T query( std::vector<T> &prefix_sum, ci32 l, ci32 r ) {
	if( l > r ) 
		return 0;

	return prefix_sum[r] - prefix_sum[ l - 1 ];
};
int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T --  ) {
		ci32 n = read<i32>();
		static char str[N];
		scanf( "%s", str + 1 );
		std::vector<i32> pre_left( n + 1 ), pre_right( n + 1 );
		std::vector<i64> sum_left( n + 1 ), sum_right( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			pre_left[i] = pre_left[ i - 1 ];
			pre_right[i] = pre_right[ i - 1 ];
			sum_left[i] = sum_left[ i - 1 ];
			sum_right[i] = sum_right[ i - 1 ];
			if( str[i] == '<' ) {
				pre_left[i] ++;
				sum_left[i] += i;
			}
			if( str[i] == '>' ) {
				pre_right[i] ++;
				sum_right[i] += i;
			}
		}
		for( int i = 1; i <= n; i ++ ) {
			if( str[i] == '<' ) {
				// ci32 k = Min( query( pre_right, 1, i - 1 ), query( pre_left, i, n ) );
				ci32 left = query( pre_right, 1, i - 1 );
				ci32 right = query( pre_left, i, n );
				ci32 k = Min( left, right );
				if( left < right ) {
					ci32 rig_border = std::lower_bound( pre_left.begin() + i, pre_left.end(), pre_left[i] + k ) - pre_left.begin();
					ci64 res = 2LL * ( - query( sum_right, 1, i ) + query( sum_left, i, rig_border ) ) - i;
					printf( "%lld ", res );
				}
				else {
					ci32 left_border = std::lower_bound( pre_right.begin(), pre_right.begin() + i, pre_right[i] - k + 1 ) - pre_right.begin();
					ci64 res = 2LL * ( - query( sum_right, left_border, i ) + query( sum_left, i, n ) ) - i + ( n + 1 );
					printf( "%lld ", res );
				}
			}
			else {
				ci32 left = query( pre_right, 1, i );
				ci32 right = query( pre_left, i + 1, n );
				ci32 k = Min( left, right );
				if( left <= right ) {
					ci32 rig_border = std::lower_bound( pre_left.begin() + i, pre_left.end(), pre_left[i] + k ) - pre_left.begin();
					ci64 res = 2LL * ( - query( sum_right, 1, i ) + query( sum_left, i, rig_border ) ) + i;
					printf( "%lld ", res );
				}
				else {
					ci32 left_border = std::lower_bound( pre_right.begin(), pre_right.begin() + i, pre_right[i] - k ) - pre_right.begin();
					ci64 res = 2LL * ( - query( sum_right, left_border, i ) + query( sum_left, i, n ) ) + i + ( n + 1 );
					printf( "%lld ", res );
				}
			}
		}
		printf( "\n" );
	}
}
