/*
 * j.cpp 2024-11-06
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
#include <cinttypes>

#include <set>
#include <map>
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
	freopen( "j.in", "r", stdin );
	freopen( "j.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		i32 started = -1;
		std::map<i32, i32> count;
		std::set<std::pair<i32, i32>> checked;
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		ci32 q = read<i32>();

		std::vector<i64> scores( m + 1 );
		for( int _ = 1; _ <= q; _ ++ ) {
			ci32 op = read<i32>();
			if( op == 1 ) {
				ci32 x = read<i32>();
				started = x;
			}
			if( op == 2 ) {
				ci32 id = read<i32>();
				ci32 x = read<i32>();

				if( checked.count( std::make_pair( id, x ) ) )
					continue;

				if( started == x ) {
					checked.insert( std::make_pair( id, x ) );
					scores[id] += m - count[x];
					count[x] ++;
				}
			}
			if( op == 3 ) { 
				ci32 id = read<i32>();
				ci32 x = read<i32>();

				if( checked.count( std::make_pair( id, x ) ) )
					continue;
				if( started == x ) 
					checked.insert( std::make_pair( id, x ) );
			}
		}

		std::vector<std::pair<i64, i32>> list;
		for( int i = 1; i <= m; i ++ ) {
			list.emplace_back( scores[i], i );
		}
		std::sort( list.begin(), list.end(), []( const auto &_a, const auto &_b ) {
			if( _a.first == _b.first ) 
				return _a.second < _b.second;
			return _a.first > _b.first;
		});
		for( auto &[s, id]: list ) 
			printf( "%d %" PRId64 "\n", id, s );

	}
}
