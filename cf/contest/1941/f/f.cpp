/*
 * f.cpp 2024-03-12
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

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	i64 T = read<i64>();
	while( T -- ) {
		ci64 n = read<i64>();
		ci64 m = read<i64>();
		ci64 k = read<i64>();
		std::vector<i64> a(n), d(m), f(k);
		std::vector<i64> diff(n - 1);
		for( auto &x: a ) 
			x = read<i64>();
		for( auto &x: d ) 
			x = read<i64>();
		for( auto &x: f ) 
			x = read<i64>();
		std::sort( d.begin(), d.end() );
		std::sort( f.begin(), f.end() );
		f.erase( std::unique( f.begin(), f.end() ), f.end() );
		d.erase( std::unique( d.begin(), d.end() ), d.end() );
		for( int i = 1; i < n; i ++ ) {
			diff[ i - 1 ] = a[i] - a[ i - 1 ];
		}
		ci64 max_gap = *std::max_element( diff.begin(), diff.end() );
		ci64 cnt = std::count( diff.begin(), diff.end(), max_gap );
		if( cnt > 1 ) {
			printf( "%lld\n", max_gap );
		}
		else {
			i64 ans = *std::max_element( diff.begin(), diff.end() );
			ci64 pos = std::find( diff.begin(), diff.end(), max_gap ) - diff.begin();
			std::swap( diff[pos], diff[ n - 2 ] );
			diff.pop_back();
			const auto max_it = std::max_element( diff.begin(), diff.end() );
			ci64 lowest = ( max_it == diff.end()? 0: *max_it );
			ci64 target = ( a[pos] + a[ pos + 1 ] ) / 2;
			for( auto &x: d ) {
				{
					auto it = std::lower_bound( f.begin(), f.end(), target - x );
					for( int i = 1; i <= 4 && it != f.begin(); i ++ ) {
						it --;
						ci64 problem = *it + x;
						if( a[pos] < problem && problem < a[ pos + 1 ] ) {
							chk_Min( ans, Max( lowest, Max( problem - a[pos], a[pos + 1] - problem  ) ) );
						}
						if( it == f.begin() ) 
							break;
					}
				}
				{
					auto it = std::lower_bound( f.begin(), f.end(), target - x );
					for( int i = 1; i <= 4 && it != f.end(); i ++ ) {
						ci64 problem = *it + x;
						if( a[pos] < problem && problem < a[ pos + 1 ] ) {
							chk_Min( ans, Max( lowest, Max( problem - a[pos], a[pos + 1] - problem  ) ) );
						}
						it ++;
						if( it == f.end() ) 
							break;
					}
				}
			}
			printf( "%lld\n", ans );
		}
	}
}
