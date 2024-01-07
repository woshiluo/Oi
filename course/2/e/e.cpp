/*
 * e.cpp 2024-01-04
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

const int N = 1e3 + 1e2;

struct Set {
	int set[N], size[N];
	void init( ci32 n ) { for( int i = 0; i <= n; i ++ ) set[i] = i; }
	int get_fa( ci32 cur ) {
		if( set[cur] == cur )
			return cur;
		set[cur] = get_fa( set[cur] );
		return set[cur];
	}
	int& operator[]( const int cur ) { 
		return set[ get_fa(cur) ];
	}
	void merge( ci32 from, ci32 to ) {
		ci32 fa_x = get_fa(from);
		ci32 fa_y = get_fa(to);
		if( fa_x == fa_y ) 
			return ;
		size[fa_y] += size[fa_x];
		set[fa_x] = fa_y;
	}
} set;

int pool[N];

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	set.init(1001);
	for( int i = 1; i <= n; i ++ ) {
		ci32 k = read<i32>();
		std::vector<i32> list(k);
		for( auto &x: list ) {
			x = read<i32>();
		}
		if( k ) { 
			set.size[ set[ list[0] ] ] ++;
			for( int j = 1; j < k; j ++ ) {
				set.merge( list[j], list[0] );
			}
		}
	}
	std::vector<i32> list;
	for( int i = 1; i <= 1000; i ++ ) {
		if( set[i] == i && set.size[i] ) {
			list.push_back( set.size[ set[i] ] );
		}
	}
	std::sort( list.begin(), list.end() );
	std::reverse( list.begin(), list.end() );
	printf( "%ld\n", list.size() );
	ci32 size = list.size();
	for( int i = 0; i < size - 1; i ++ ) 
		printf( "%d ", list[i] );
	printf( "%d", list.back() );
}
