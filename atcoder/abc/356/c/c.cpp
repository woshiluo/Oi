/*
 * c.cpp 2024-06-01
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

int full_pow( ci32 cur ) { return 1 << cur; }
bool chk_pos( ci32 cur, ci32 pos ) { return ( cur >> pos ) & 1; }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();
	ci32 k = read<i32>();
	std::vector<std::pair<std::vector<i32>, bool>> atts;
	for( int i = 0; i < m; i ++ ) {
		std::vector<i32> list( read<i32>() );

		for( auto &x: list ) {
			x = read<i32>();
		}

		static char op[3];
		scanf( "%s", op );
		atts.push_back(std::make_pair(list, op[0] == 'o'));
	}

	i32 ans = 0;
	for( int mask = 0; mask < full_pow(n); mask ++ ) {
		bool valid = true;
		for( auto &[att, result]: atts ) {
			i32 count = 0;
			for( auto &x: att ) {
				if( chk_pos( mask, x - 1 ) ) 
					count ++;
			}
			if( ( count >= k ) != result )
				valid = false;
		}
		ans += valid;
	}

	printf( "%d\n", ans );
	
}
