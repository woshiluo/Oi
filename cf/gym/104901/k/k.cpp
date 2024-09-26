/*
 * k.cpp 2024-09-20
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
	freopen( "k.in", "r", stdin );
	freopen( "k.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci64 k = read<i64>();
		std::vector<i32> a(n + 1);

		for( int i = 0; i < n; i ++ ) 
			a[i] = read<i32>() - i;

		i64 sm_sum = 0, lg_sum = 0;
		std::multiset<i32> sm, lg;
		const auto remove_sm = [&]( ci32 x ) {
			sm_sum -= x;
			sm.erase( sm.find(x) );
		};
		const auto remove_lg = [&]( ci32 x ) {
			lg_sum -= x;
			lg.erase( lg.find(x) );
		};
		const auto add_sm = [&]( ci32 x ) {
			sm_sum += x;
			sm.insert(x);
		};
		const auto add_lg = [&]( ci32 x ) {
			lg_sum += x;
			lg.insert(x);
		};
		const auto add = [&]( ci32 x ) {
			if( lg.size() == 0 && sm.size() == 0 ) 
				add_sm(x);
			else if( lg.size() == 0 )
				add_sm(x);
			else if( sm.size() == 0 )
				add_lg(x);
			else {
				ci32 mid = *sm.rbegin();
				if( x <= mid ) 
					add_sm(x);
				else 
					add_lg(x);
			}
		};
		const auto balance = [&]() {
			while( lg.size() < sm.size() ) {
				ci32 sm_max = *sm.rbegin();
				remove_sm( sm_max );
				add_lg( sm_max );
			}
			while( sm.size() < lg.size() ) {
				ci32 lg_min = *lg.begin();
				remove_lg( lg_min );
				add_sm( lg_min );
			}
		};
		const auto get_k = [&]() {
			if( sm.size() + lg.size() <= 1 )
				return (i64)0;
			balance();
			ci64 mid = *sm.rbegin();
			ci64 sm_diff = mid * sm.size() - sm_sum;
			ci64 lg_diff = lg_sum - mid * lg.size();
			return sm_diff + lg_diff;
		};

		const auto try_remove = [&]( ci32 x ) {
			if( sm.count( x ) ) 
				remove_sm( x );
			else if( lg.count( x ) ) 
				remove_lg( x );
		};

		i32 res = 0;
		i32 p = -1;
		for( int i = 0; i < n; i ++ ) {
			if( i ) {
				try_remove( a[ i - 1 ] );
			}

			chk_Max( p, i - 1 );
			while( p + 1 <= n && get_k() <= k ) {
				chk_Max( res, p - i + 1 );
				p ++;
				add( a[p] );
			}

			try_remove( a[p] );
			p --;
		}

		printf( "%d\n", res );
	}
	
}
