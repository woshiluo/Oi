/*
 * j.cpp 2024-07-23
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
const int K = 20;

char str[N];

int nxt[N][K], cnt_a[N][K], cnt_b[N][K];

int main() {
#ifdef woshiluo
	freopen( "j.in", "r", stdin );
	freopen( "j.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 b = read<i32>();
	ci32 a = read<i32>();

	static char buf[N];
	scanf( "%s", buf );

	int p = 1;
	while( p < n + 2 * b + 4 ) {
		strcpy( str + p, buf );
		p += n;
	}
	p --;

	std::vector<i32> sum( p + 1, 0 );
	for( int i = 1; i <= p; i ++ ) {
		sum[i] = sum[ i - 1 ];
		sum[i] += ( str[i] == '1' );
	}

	const auto len = [] ( ci32 left, ci32 rig ) { return rig - left + 1; };
	const auto query_a = [&]( ci32 left, ci32 rig ) { return sum[rig] - sum[ left - 1 ]; };
	const auto query_b = [&]( ci32 left, ci32 rig ) { return len( left, rig ) - query_a( left, rig ); };

	for( int i = 1; i <= n; i ++ ) {
		i32 left = i, rig = p, res = p;
		while( left <= rig ) {
			ci32 mid = ( left + rig ) >> 1;
			if( query_a( i, mid ) >= b || query_b( i, mid ) >= b ) {
				res = mid;
				rig = mid - 1;
			}
			else
				left = mid + 1;
		}

		nxt[i][0] = ( res % n ) + 1;

		if( query_a( i, res ) >= b ) {
			cnt_a[i][0] = 1;
			cnt_b[i][0] = 0;
		}
		else {
			cnt_a[i][0] = 0;
			cnt_b[i][0] = 1;
		}
	}

	for( int k = 1; k < K; k ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			nxt[i][k] = nxt[ nxt[i][ k - 1 ] ][ k - 1 ];
			cnt_a[i][k] = cnt_a[i][ k - 1 ] + cnt_a[ nxt[i][ k - 1 ] ][ k - 1 ];
			cnt_b[i][k] = cnt_b[i][ k - 1 ] + cnt_b[ nxt[i][ k - 1 ] ][ k - 1 ];
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		i32 cur = i;
		i32 win_a = 0, win_b = 0;
		for( int k = K - 1; k >= 0; k -- ) {
			if( win_a + cnt_a[cur][k] < a && win_b + cnt_b[cur][k] < a ) {
				win_a += cnt_a[cur][k];
				win_b += cnt_b[cur][k];
				cur = nxt[cur][k];
			}
		}
		win_a += cnt_a[cur][0];
		win_b += cnt_b[cur][0];
		if( win_a == a ) 
			printf( "1" );
		else
			printf( "0" );
	}
	
}
