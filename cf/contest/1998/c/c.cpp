/*
 * c.cpp 2024-08-10
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

#include <functional>
#include <vector>
#include <algorithm>

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;


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
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 k = read<i32>();

		std::vector<i64> a(n), b(n), l1, l2;
		for( auto &x: a )
			x = read<i32>();
		for( auto &x: b ) 
			x = read<i32>();
		
		for( int i = 0; i < n; i ++) { 
			if( b[i] ) 
				l1.push_back( a[i] );
			else 
				l2.push_back( a[i] );
		}

		std::sort( l1.begin(), l1.end() );
		std::reverse( l1.begin(), l1.end() );
		std::sort( l2.begin(), l2.end() );

		ci32 tar = ( ( n - 1 ) + 1 ) / 2 - 1;
		i64 ans = 0;
		{
			const int K = 21;
			i32 cnt = 0;
			tree<i64, null_type, std::less<i64>, rb_tree_tag, tree_order_statistics_node_update> t;
			std::vector<i64> list;
			for( auto &x: l2 ) {
				cnt ++;
				t.insert( ( x << K ) + cnt );
			}
			for( auto x: l1 ) {
				cnt ++;

				t.insert( ( x << K ) + cnt );
				list.push_back( ( x << K ) + cnt );
			}

			for( auto &x: list ) {
				t.erase(x);
				ci64 middle = *t.find_by_order(tar) >> K;
				chk_Max( ans, middle + ( x >> K ) + k );
				t.insert(x);
			}
		}
		auto check = [&] ( ci64 mid ) {
			const int K = 21;
			i32 cnt = 0;
			tree<i64, null_type, std::less<i64>, rb_tree_tag, tree_order_statistics_node_update> t;
			for( auto &x: l2 ) {
				cnt ++;
				t.insert( ( x << K ) + cnt );
			}
			i64 less = k;
			for( auto x: l1 ) {
				cnt ++;

				if( x <= mid ) {
					ci64 p = Min( less, mid - x );
					less -= p;
					x += p;
				}

				t.insert( ( x << K ) + cnt );
			}

			if( ( *t.find_by_order(tar) >> K ) < mid ) 
				return false;

			return true;
		};

		if( l2.size() ) {
			ci64 base = l2.back(); l2.pop_back();
			i64 left = 0, rig = 1e10, res = 0;
			while( left <= rig ) {
				ci64 mid = ( left + rig ) >> 1;
				if( check(mid) ) {
					res = mid;
					left = mid + 1;
				}
				else
					rig = mid - 1;
			}
			chk_Max( ans, base + res );
		}
		printf( "%" PRId64 "\n", ans );
	}
}
