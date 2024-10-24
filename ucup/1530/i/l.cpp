/*
 * l.cpp 2024-10-16
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

#include <queue>
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

ci32 MAX_X = 65536;

std::vector<i32> list[MAX_X];

int main() {
#ifdef woshiluo
	freopen( "l.in", "r", stdin );
	freopen( "l.out", "w", stdout );
#endif

	i32 m = read<i32>();
	ci32 n = read<i32>();
	ci32 x = read<i32>();
	std::priority_queue<i32, std::vector<i32>, std::greater<i32> > q;
	for( int i = 1; i <= n; i ++ ) {
		q.push( read<i32>() );
	}
	i32 res = 0, tot = 0;
	for( int i = 1; i <= x; i ++ ) {
		for( auto &y: list[i] ) {
			q.push(y);
			res ++;
		}
		while( !q.empty() && tot < m ) {
			list[ i + q.top() ].push_back( q.top() );
			q.pop();
			tot ++;
		}
	}
	for( auto &y: list[x + 1] ) {
		q.push(y);
		res ++;
	}
	printf( "%d %d\n", m - tot, tot - res );
}
