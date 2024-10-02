/*
 * j.cpp 2024-10-02
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

const int N = 1024;
const int M = 2e6 + 1e5;


std::vector<i32> nodes_x[N], nodes_y[N];
std::vector<i32> nodes_xr[N], nodes_yr[N];

int main() {
#ifdef woshiluo
	freopen( "j.in", "r", stdin );
	freopen( "j.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();
	for( int i = n; i >= 1; i -- ) {
		static char buf[N];
		scanf( "%s", buf + 1 );
		for( int j = 1; j <= m; j ++ ) {
			if( buf[j] == '#' ) {
				nodes_x[j].push_back(i);
				nodes_y[i].push_back(j);
			}
		}
	}
	for( int i = 1; i <= m; i ++ ) {
		std::sort( nodes_x[i].begin(), nodes_x[i].end() );
		nodes_xr[i] = nodes_x[i];
		std::reverse( nodes_xr[i].begin(), nodes_xr[i].end() );
	}
	for( int i = 1; i <= n; i ++ ) {
		std::sort( nodes_y[i].begin(), nodes_y[i].end() );
		nodes_yr[i] = nodes_y[i];
		std::reverse( nodes_yr[i].begin(), nodes_yr[i].end() );
	}

	{
		static char buf[M];
		scanf( "%s", buf + 1 ); 
		i32 x = 1, y = 1;
		ci32 len = strlen(buf + 1);
		for( int i = 1; i <= len; i ++ ) {
			if( buf[i] == 'U' ) {
				const auto &current_list = nodes_x[x];
				auto it = std::upper_bound( current_list.begin(), current_list.end(), y );
				if( it == current_list.end() ) 
					y = n;
				else 
					y = *it - 1;
			}
			if( buf[i] == 'D' ) {
				const auto &current_list = nodes_xr[x];
				auto it = std::upper_bound( current_list.begin(), current_list.end(), y, []( const auto &_a, const auto &_b ) { return _a > _b; } );
				if( it == current_list.end() ) 
					y = 1;
				else 
					y = *it + 1;
			}
			if( buf[i] == 'R' ) {
				const auto &current_list = nodes_y[y];
				auto it = std::upper_bound( current_list.begin(), current_list.end(), x );
				if( it == current_list.end() ) 
					x = m;
				else 
					x = *it - 1;
			}
			if( buf[i] == 'L' ) {
				const auto &current_list = nodes_yr[y];
				auto it = std::upper_bound( current_list.begin(), current_list.end(), x, []( const auto &_a, const auto &_b ) { return _a > _b; } );
				if( it == current_list.end() ) 
					x = 1;
				else 
					x = *it + 1;
			}
		}
		printf( "%d %d\n", x, y );
	}
	return 0;
}
