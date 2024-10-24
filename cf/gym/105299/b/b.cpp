/*
 * b.cpp 2024-10-03
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
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
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

const int N = 1e5 + 1e4;

int a[N];
int sum[N];

int rev_sum[N];
int pre_min[N], pre_max[N];
int suf_min[N], suf_max[N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<i32>();
		sum[i] = sum[ i - 1 ] + ( a[i] == 0? -1: 1 );
	}
	for( int i = n; i >= 1; i -- ) {
		rev_sum[i] = rev_sum[ i + 1 ] + ( a[i] == 0? -1: 1 );
	}
	for( int i = 1; i <= n; i ++ ) {
		pre_min[i] = pre_min[ i - 1 ];
		pre_max[i] = pre_max[ i - 1 ];
		if( rev_sum[i] < rev_sum[ pre_min[i] ] )
			pre_min[i] = i;
		if( rev_sum[i] > rev_sum[ pre_max[i] ] )
			pre_min[i] = i;
	}
	suf_min[ n + 1 ] = suf_max[ n + 1 ] = n;
	for( int i = n; i >= 1; i -- ) {
		suf_min[i] = suf_min[ i + 1 ];
		suf_max[i] = suf_max[ i + 1 ];
		if( sum[i] < sum[ suf_min[i] ] )
			suf_min[i] = i;
		if( sum[i] > sum[ suf_max[i] ] )
			suf_min[i] = i;
	}

	auto query = [&] ( ci32 left, ci32 rig ) { return rig - left + 1; };
	auto calc = [&] ( ci32 left,  ci32 rig ) -> i64 { return pow( (i64)( rig - left +  1 ), 2 ); };
	i32 st = 0, ed = 0;
	for( int i = 1; i <= n; i ++ ) {
		ci32 n1 = suf_max[ i + 1 ];
		ci32 n2 = suf_min[ i + 1 ];
		if( query( i, n1 ) > query( st, ed ) )
			st = i, ed = n1;
		if( query( i, n2 ) > query( st, ed ) )
			st = i, ed = n2;
	}

	i64 res = calc( st, ed );
	while( st != 1 || ed != n ) {
		if( st != 1 ) 
			st = pre_max[ st - 1 ];
		if( ed != n ) 
			ed = suf_max[ ed + 1 ];
		res += calc( st, ed );
	}
}
