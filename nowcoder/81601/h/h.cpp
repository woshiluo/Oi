/*
 * h.cpp 2024-08-01
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

const int N = 1e6 + 1e5;

int main() {
#ifdef woshiluo
	freopen( "h.in", "r", stdin );
	freopen( "h.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		static char str[N];
		scanf( "%s", str );
		ci32 len = strlen(str);

		auto get_id = [&]( ci32 p ) {
			if( str[p] == 'U' ) 
				return 3;
			if( str[p] == '5' ) 
				return 2;
			if( str[p] == '4' ) 
				return 1;
			if( str[p] == '3' ) 
				return 0;
			return 0;
		};

		bool flag = true;
		int sum_10[5], sum_90[5], la_pos = -1;
		memset( sum_10, 0, sizeof(sum_10) );
		memset( sum_90, 0, sizeof(sum_90) );
		for( int i = 0; i < len; i ++ ) {
			if( i >= 10 ) {
				sum_10[ get_id(i - 10) ] --;
			}
			if( i >= 90 ) {
				sum_90[ get_id(i - 90) ] --;
			}

			sum_10[ get_id(i) ] ++;
			sum_90[ get_id(i) ] ++;

			if( get_id(i) == 2 && la_pos != -1 ) {
				if( get_id( la_pos ) != 3 ) {
					flag = false;
					break;
				}
			}
			if( get_id(i) >= 2 ) 
				la_pos = i;

			if( i >= 89 && sum_90[2] + sum_90[3] == 0 ) {
				flag = false;
				break;
			}

			if( i >= 9 && sum_10[1] + sum_10[2] + sum_10[3] == 0 ) {
				flag = false;
				break;
			}

		}

		if( flag )
			printf( "valid\n" );
		else 
			printf( "invalid\n" );
	}
	
}
