/*
 * 5.cpp 2024-08-12
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
	freopen( "5.in", "r", stdin );
	freopen( "5.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		const auto get_len = []( ci64 l, ci64 r ) -> i64 { return r - l + 1; };

		ci64 l = read<i64>();
		ci64 r = read<i64>();
		ci64 k = read<i64>();

		std::priority_queue<i64> q;
		std::set<i64> in;
		std::map<i64, std::map<i64, i64>> mp;

		q.push( get_len( l, r ) );
		in.insert( get_len( l, r ) );
		mp[get_len(l, r)][0] = 1;
		i64 res = 0;
		while( !q.empty() ) {
			ci64 len = q.top(); q.pop();
			const auto &cur_mp = mp[len];
			ci64 left = 1, rig = len;
			ci64 mid = ( left + rig ) >> 1;
			ci64 lpart = get_len( left, mid - 1 );
			ci64 rpart = get_len( mid + 1, rig );
			if( left <= mid - 1 ) {
				auto &nxt_mp = mp[lpart];
				for( auto &[tlen, tcnt]: cur_mp ) {
					if( tlen + 1 <= k ) 
						nxt_mp[ tlen + 1 ] += tcnt;
				}
				if( in.count( lpart ) == 0 ) {
					in.insert( lpart );
					q.push( lpart );
				}
			}
			if( mid + 1 <= rig ) {
				auto &nxt_mp = mp[rpart];
				for( auto &[tlen, tcnt]: cur_mp ) {
					nxt_mp[tlen] += tcnt;
				}
				if( in.count( rpart ) == 0 ) {
					in.insert( rpart );
					q.push( rpart );
				}
			}

			for( auto &[tlen, tcnt]: cur_mp ) {
				res += tcnt;
			}
		}

		printf( "%" PRId64 "\n", res );
	}
}
