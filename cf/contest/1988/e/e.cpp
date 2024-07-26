/*
 * e.cpp 2024-07-17
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

#include <set>
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
const int INF = 0x3f3f3f3f;

const int K = 20;

int a[N];
int pl[N], pb[N], sl[N], sb[N];
int p2l[N], s2l[N];
i64 pls[N], sls[N], val[N], diff[N];

i32 log_2[N], pow_2[K];
i32 min[N][K], max[N][K];

void gen_st( int n ) {
	for( int i = 2; i <= n; i ++ ) {
		log_2[i] = log_2[ i >> 1 ] + 1;
	}
	pow_2[0] = 1;
	for( int i = 1; i < K; i ++ ) {
		pow_2[i] = pow_2[ i - 1 ] << 1;
	}

	for( int k = 1; k < K; k ++ ) {
		for( int i = 1; i <= n; i ++) {
			if( i + pow_2[k] - 1 > n ) {
				min[i][k] = INF;
				max[i][k] = -INF;
				continue;
			}
			min[i][k] = Min( min[i][ k - 1 ], min[ i + pow_2[ k - 1 ] ][ k - 1 ] );
			max[i][k] = Max( max[i][ k - 1 ], max[ i + pow_2[ k - 1 ] ][ k - 1 ] );
		}
	}
}


int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();

		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<i32>();
			min[i][0] = a[i];
			max[i][0] = a[i];
		}

		gen_st(n);

		const auto query_st = [&]( const int left, const int rig, const bool max_flag ) {
			ci32 len = ( rig - left + 1 );
			ci32 k = log_2[len];
			if( max_flag ) 
				return Max( max[left][k], max[ rig - pow_2[k] + 1 ][k] );
			else
				return Min( min[left][k], min[ rig - pow_2[k] + 1 ][k] );
		};

		const auto check_rig = [&]( const int from, const int to, const int base, const bool max_flag ) {
			i32 left = from, rig = to, res = to + 1;
			while( left <= rig ) {
				ci32 mid = ( left + rig ) >> 1;
				ci32 cur = query_st( from, mid, max_flag );
				if( max_flag? ( cur > base ): ( cur < base ) ) {
					res = mid;
					rig = mid - 1;
				}
				else
					left = mid + 1;
			}
			return res;
		};

		const auto check_left = [&]( const int from, const int to, const int base, const bool max_flag ) {
			i32 left = from, rig = to, res = from - 1;
			while( left <= rig ) {
				ci32 mid = ( left + rig ) >> 1;
				ci32 cur = query_st( mid, to, max_flag );
				if( max_flag? ( cur > base ): ( cur < base ) ) {
					res = mid;
					left = mid + 1;
				}
				else
					rig = mid - 1;
			}
			return res;
		};


		auto gen_cnt = [&]( ci32 left, ci32 rig, ci32 mid ) { return 1LL * ( mid - left + 1 ) * ( rig - mid + 1 ); };
		for( int i = 1; i <= n; i ++ ) {
			pb[i] = check_left( 1, i - 1, a[i], 1 );
			pl[i] = check_left( 1, i - 1, a[i], 0 );

			sb[i] = check_rig( i + 1, n, a[i], 1 );
			sl[i] = check_rig( i + 1, n, a[i], 0 );

			p2l[i] = check_left( 1, pl[i] - 1, a[i], 0 );
			s2l[i] = check_rig( sl[i] + 1, n, a[i], 0 );
		}

		i64 res = 0;
		pls[0] = sls[0] = pls[ n + 1 ] = sls[ n + 1 ] = 0;
		for( int i = 1; i <= n; i ++ ) {
			val[i] = 1LL * gen_cnt( pl[i] + 1, sl[i] - 1, i ) * a[i];

			// printf( "%d: %d %d %d %lld\n", i, a[i], pl[i] + 1, sl[i] - 1, val[i] );
			res += val[i];
			pls[i] = pls[ pl[i] ] + 1LL * a[i] * gen_cnt( pl[i] + 1, i, i );
		}

		for( int i = n; i >= 1; i -- ) {
			sls[i] = sls[ sl[i] ] + 1LL * a[i] * gen_cnt( i, sl[i] - 1, i );
		}


		for( int i = 0; i <= n + 1; i ++ ) {
			diff[i] = 0;
		}
		for( int i = 1; i <= n; i ++ ) {
			diff[ pl[i] ] -= val[i];
			diff[ pl[i] ] += 1LL * a[i] * gen_cnt( p2l[i] + 2, sl[i] - 1, i );
			diff[ sl[i] ] -= val[i];
			diff[ sl[i] ] += 1LL * a[i] * gen_cnt( pl[i] + 1, s2l[i] - 2, i );
		}

		for( int i = 1; i <= n; i ++ ) {
			i64 cur_res = res - val[i];
			cur_res -= sls[i] + pls[i];
			cur_res += a[i] * ( gen_cnt( pl[i] + 1, i, i ) + gen_cnt( i, sl[i] - 1, i ) );
			cur_res += diff[i];

			printf( "%lld ", cur_res );
		}
		printf( "\n" );
	}
}
