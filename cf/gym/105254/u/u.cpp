/*
 * u.cpp 2024-10-01
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

int main() {
#ifdef woshiluo
	freopen( "u.in", "r", stdin );
	freopen( "u.out", "w", stdout );
#endif

	
	ci32 s = read<i32>();
	ci32 c = read<i32>() - 4; 


	ci32 both_c = c / 8;
	ci32 both_c2 = ( c - 2 ) / 8;
	ci32 both_c3 = ( c - 4 ) / 8;
	ci32 both_c4 = ( c - 6 ) / 8;
	ci32 less_c = ( c % 8 );
	bool avi_replace = ( less_c >= 4 );
	bool f1 = true;
	bool f2 = ( c >= 2 && s >= 2 );
	bool f3 = ( c >= 4 && s >= 2 );
	bool f4 = ( c >= 6 && s >= 2 );
	int c1 = both_c * 8 + 4;
	int c2 = f2? ( both_c2 * 8 + 6 ): 0;
	int c3 = f3? ( both_c3 * 8 + 8 ): 0;
	int c4 = f4? ( both_c4 * 8 + 10 ): 0;
	if( f2 && c2 > c1 && c2 > c3 && c2 > c4 ) {
		ci32 cnt_s = ( s - 2 ) / 2;
		printf( "R" );
		for( int i = 1; i <= both_c2; i ++ ) 
			printf( "LR" );
		for( int i = 1; i <= cnt_s; i ++ ) 
			printf( "S" );
		for( int i = 1; i <= both_c2; i ++ ) 
			printf( "RL" );
		printf("RLRR");
		for( int i = 1; i <= both_c2; i ++ ) 
			printf( "LR" );
		for( int i = 1; i <= cnt_s + 1; i ++ ) 
			printf( "S" );
		for( int i = 1; i <= both_c2; i ++ ) 
			printf( "RL" );
		printf( "RS" );
	}
	else if( f3 && c3 > c1 && c3 > c4 ) {
		ci32 cnt_s = ( s - 2 ) / 2;
		printf( "R" );
		for( int i = 1; i <= both_c3; i ++ ) 
			printf( "LR" );
		for( int i = 1; i <= cnt_s + 1; i ++ ) 
			printf( "S" );
		for( int i = 1; i <= both_c3; i ++ ) 
			printf( "RL" );
		printf("RLRR");
		for( int i = 1; i <= both_c3; i ++ ) 
			printf( "LR" );
		for( int i = 1; i <= cnt_s + 1; i ++ ) 
			printf( "S" );
		for( int i = 1; i <= both_c3; i ++ ) 
			printf( "RL" );
		printf( "RLR" );
	}
	else if( f4 && c4 > c1 ) {
		ci32 cnt_s = ( s - 2 ) / 2;
		printf( "RLR" );
		for( int i = 1; i <= both_c4; i ++ ) 
			printf( "LR" );
		for( int i = 1; i <= cnt_s; i ++ ) 
			printf( "S" );
		for( int i = 1; i <= both_c4; i ++ ) 
			printf( "RL" );
		printf( "RLRRSLR" );
		for( int i = 1; i <= both_c4; i ++ ) 
			printf( "LR" );
		for( int i = 1; i <= cnt_s; i ++ ) 
			printf( "S" );
		for( int i = 1; i <= both_c4; i ++ ) 
			printf( "RL" );
		printf( "RS" );
	}
	else {
		if( s >= 4 && avi_replace ) {
			ci32 cnt_s = ( s - 4 ) / 2;
			printf( "R" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "LR" );
			printf( "S" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "RL" );
			printf( "R" );
			for( int i = 1; i <= cnt_s; i ++ ) 
				printf( "S" );
			printf( "LRRL" );
			printf( "R" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "LR" );
			printf( "S" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "RL" );
			printf( "R" );
			for( int i = 1; i <= cnt_s + 2; i ++ ) 
				printf( "S" );
		}
		else if( both_c > 0 && avi_replace ) {
			printf( "R" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "LR" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "RL" );
			printf( "R" );
			printf( "LR" );
			printf( "R" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "LR" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "RL" );
			printf( "R" );
			printf( "LR" );
		}
		else {
			ci32 cnt_s = s / 2;
			printf( "R" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "LR" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "RL" );
			printf( "R" );
			for( int i = 1; i <= cnt_s; i ++ ) 
				printf( "S" );
			printf( "R" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "LR" );
			for( int i = 1; i <= both_c; i ++ ) 
				printf( "RL" );
			printf( "R" );
			for( int i = 1; i <= cnt_s; i ++ ) 
				printf( "S" );
		}
	}
}
