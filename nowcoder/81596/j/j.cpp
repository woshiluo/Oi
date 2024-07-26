/*
 * j.cpp 2024-07-17
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

const int N = 1e5 + 1e4;
const int K = 20;

i64 log_2[N], pow_2[K];
i64 min[2][N][K], max[2][N][K], asum[2][N];

// 0/1 x/y
// 0/1 0/{n,m}
bool ed0[2][2][N][K];
i32 opc[2][2][N][K];
i64 stc[2][2][N][K];

void gen_st() {
}

int main() {
#ifdef woshiluo
	freopen( "j.in", "r", stdin );
	freopen( "j.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();

	ci32 k = read<i32>();
	ci32 q = read<i32>();

	std::vector<i64> sum[2] = { std::vector<i64>( k + 1 ), std::vector<i64>( k + 1 ) };
	for( int i = 1; i <= k; i ++ ) {// {{{
		static char op[8];
		scanf( "%s", op );
		ci32 x = read<i32>();

		if( op[0] == 'U' ) {
			sum[0][i] = 0;
			sum[1][i] = x;

			asum[0][i] = 0;
			asum[1][i] = x;
		}
		if( op[0] == 'D' ) {
			sum[0][i] = 0;
			sum[1][i] = -x;

			asum[0][i] = 0;
			asum[1][i] = x;
		}
		if( op[0] == 'L' ) {
			sum[0][i] = -x;
			sum[1][i] = 0;

			asum[0][i] = x;
			asum[1][i] = 0;
		}
		if( op[0] == 'R' ) {
			sum[0][i] = x;
			sum[1][i] = 0;

			asum[0][i] = 0;
			asum[1][i] = x;
		}
	}// }}}
	for( int i = 1; i <= k; i ++ ) {
		sum[0][i] += sum[0][ i - 1 ];
		sum[1][i] += sum[1][ i - 1 ];
	}

	gen_st();

	auto query_st_min = [&] ( const int left, const int rig, int p ) {
		ci32 len = ( rig - left + 1 );
		ci32 q = log_2[len];
		return Min( min[p][left][q], min[p][ rig - pow_2[q] ][q] );
	};
	auto query_st_max = [&] ( const int left, const int rig, int p ) {
		ci32 len = ( rig - left + 1 );
		ci32 q = log_2[len];
		return Max( max[p][left][q], max[p][ rig - pow_2[q] ][q] );
	};

	auto chk_nxt_0 = [&] ( const int from, const int to, const int p, const int st ) {
		i32 left = from, rig = to, res = to;
		while( left <= rig ) {
			ci32 mid = ( left + rig ) >> 1;
			if( st + query_st_min( from, mid, p ) <= 0 ) {
				res = mid;
				rig = mid - 1;
			}
			else 
				left = mid + 1;
		}
		return res;
	};
	auto chk_nxt_n = [&] ( const int from, const int to, const int p, const int st ) {
		ci32 tar = (p == 0)? n: m;
		i32 left = from, rig = to, res = to;
		while( left <= rig ) {
			ci32 mid = ( left + rig ) >> 1;
			if( st + query_st_max( from, mid, p ) >= tar ) {
				res = mid;
				rig = mid - 1;
			}
			else 
				left = mid + 1;
		}
		return res;
	};

	auto get_sum = [&]( const int left, const int rig, const int p, const bool abs_flag ) {
		if( abs_flag ) 
			return asum[p][rig] - asum[p][ left - 1 ];
		else 
			return sum[p][rig] - sum[p][ left - 1 ];
	};

	for( int i = k; i >= 1; i -- ) {
		for( int p = 0; p < 2; p ++ ) {
			for( int st_flag = 0; st_flag < 2; st_flag ++ ) {
				ci32 st = st_flag? ( ( p == 0 )? n: m ): 0;
				
				ci32 pos_0 = chk_nxt_0( i, k, p, st );
				ci32 pos_n = chk_nxt_n( i, k, p, st );

				ed0[p][st_flag][i][0] = pos_n < pos_0;
				ci32 min_pos = Min( pos_0, pos_n );
				opc[p][st_flag][i][0] = min_pos - i;
				stc[p][st_flag][i][0] = 
			}
		}
	}

	return 0;
}
