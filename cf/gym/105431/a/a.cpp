/*
 * a.cpp 2024-10-23
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

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	ci32 xs = read<i32>();
	ci32 ys = read<i32>();
	ci32 xt = read<i32>();
	ci32 yt = read<i32>();
	ci32 xp = read<i32>();
	ci32 yp = read<i32>();

	bool swap_x = false;
	bool swap_y = false;
	if( xs > xt ) 
		swap_x = true;
	if( ys > yt ) 
		swap_y = true;

	const auto get_mapped = [&]( i32 x, i32 y ) { return std::make_pair( (swap_x? -1: 1) * x, (swap_y? -1: 1) * y ); };
	const auto print_node = [&]( i32 x, i32 y ) { 
		printf( "%d %d\n", (swap_x? -1: 1) * x, (swap_y? -1: 1) * y ); 
	};

	const auto [msx, msy] = get_mapped( xs, ys );
	const auto [mtx, mty] = get_mapped( xt, yt );
	const auto [mpx, mpy] = get_mapped( xp, yp );

	if( mpy < msy ) {
		if( mpx < msx ) {
			printf( "1\n");
			print_node( mtx, msy );
		}
		else if( mpx < mtx ) {
			printf( "2\n");
			print_node( msx, 1e9 );
			print_node( mtx, 1e9 );
		}
		else {
			printf( "1\n");
			print_node( msx, mty );
		}
	}
	else if( mpy < mty ) {
		if( mpx < msx ) {
			printf( "2\n");
			print_node( 1e9, msy );
			print_node( 1e9, mty );
		}
		else if( mpx < mtx ) {
			printf( "3\n");
			print_node( msx, -1e9 );
			print_node( 1e9, -1e9 );
			print_node( 1e9, mty );
		}
		else {
			printf( "2\n");
			print_node( -1e9, msy );
			print_node( -1e9, mty );
		}
	}
	else {
		if( mpx < msx ) {
			printf( "1\n");
			print_node( mtx, msy );
		}
		else if( mpx < mtx ) {
			printf( "2\n");
			print_node( msx, -1e9 );
			print_node( mtx, -1e9 );
		}
		else {
			printf( "1\n");
			print_node( msx, mty );
		}
	}

	return 0;
}
