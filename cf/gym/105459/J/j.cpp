/*
 * j.cpp 2024-10-30
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

void work() {
	ci32 n = read<i32>();
	ci32 m = read<i32>();
	std::vector<i32> a( n + 1 );
	for( int i = 1; i <= n; i ++ )
		a[i] = read<i32>();
	std::vector<std::vector<i64>> list( n + 1 );
	for( int i = 1; i <= m; i ++ ) {
		ci32 x = read<i32>();
		ci32 t = read<i32>();
		list[t].push_back(x);
	}
	for( int i = 1; i <= n; i ++ ) {
		list[i].push_back( INT64_MAX / 2 );
		std::reverse( list[i].begin(), list[i].end() );
	}
	std::vector<i32> b = a;
	std::multiset<std::pair<i64, i32>> set;
	std::multiset<std::pair<i64, i32>> out;
	for( int i = 1; i <= n; i ++ ) {
		set.insert( std::make_pair( list[i].back(), i ) );
		list[i].pop_back();
	}
	i64 cur = 0;
	while(1) {
		while( !set.empty() && set.begin() -> first <= cur ) {
			const auto [time, id] = *set.begin();
			set.erase( set.begin() );
			b[id] = a[id];
			if( list[id].size() ) {
				set.insert( std::make_pair( list[id].back(), id ) );
				list[id].pop_back();
			}
		}
		while( !out.empty() && out.begin() -> first <= cur ) {
			const auto [time, id] = *out.begin();
			out.erase( out.begin() );
			b[id] = a[id];
			if( list[id].size() ) {
				set.insert( std::make_pair( list[id].back(), id ) );
				list[id].pop_back();
			}
		}
		if( set.empty() ) 
			break;
		const auto [time, id] = *set.begin();
		i64 min_time = time;
		if( !out.empty() && out.begin() -> first < time )
			chk_Min( min_time, out.begin() -> first );
		set.erase( set.begin() );
		if( cur + b[id] > min_time ) {
			b[id] -= min_time - cur;
			cur = min_time;
			set.insert( std::make_pair( time, id ) );
		}
		else {
			cur += b[id];
			b[id] = 0;
			if( list[id].size() ) {
				out.insert( std::make_pair(time, id) );
			}
		}
	}
	printf( "%" PRId64 "\n", cur );
}

int main() {
#ifdef woshiluo
	freopen( "j.in", "r", stdin );
	freopen( "j.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		work();
	}
	
	return 0;
}
