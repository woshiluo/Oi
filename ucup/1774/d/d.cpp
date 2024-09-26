/*
 * d.cpp 2024-09-21
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
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 k = read<i32>();
		ci32 m = read<i32>();
		std::vector<i32> a(n);
		for( auto &x: a ) 
			x = read<i32>();
		std::sort( a.begin(), a.end() );
		if( k & 1 ) {
			i32 sm = 0, lg = 0, eq = -1;
			for( auto &x: a ) {
				if( x == m ) 
					eq ++;
				if( x < m ) 
					sm ++;
				if( x > m ) 
					lg ++;
			}
			if( eq < 0 ) {
				printf( "NIE\n" );
				continue;
			}

			ci32 target = ( k >> 1 );

			if( sm < target ) {
				ci32 d = Min( target - sm, eq );
				eq -= d;
				sm += d;
			}
			if( lg < target ) {
				ci32 d = Min( target - lg, eq );
				eq -= d;
				lg += d;
			}

			if( sm >= target && lg >= target ) {
				printf( "TAK\n" );
				continue;
			}
			else {
				printf( "NIE\n" );
				continue;
			}
		}
		else {
			ci32 target = ( k - 2 ) >> 1;
			std::vector<i32> sum( n + 1 );
			std::map<i32, i32> mp;
			for( auto &x: a ) {
				if( mp.count(x) == 0 ) {
					ci32 id = mp.size() + 1;
					mp[x] = id;
				}
				x = mp[x];
				sum[x] ++;
			}
			for( int i = 1; i <= n; i ++ )
				sum[i] += sum[ i - 1 ];
			bool flag = false;
			for( const auto &[ p, _ ]: mp ) {
				ci32 q = m * 2 - p;
				if( mp.count(p) == 0 || mp.count(q) == 0 )
					continue;
				if( p == q ) {
					i32 sm = sum[ mp[p] - 1 ];
					i32 lg = n - sum[mp[p]];
					i32 eq = sum[mp[p]] - sm - 2;
					if( eq < 0 ) 
						continue;

					if( sm < target ) {
						ci32 d = Min( target - sm, eq );
						eq -= d;
						sm += d;
					}
					if( lg < target ) {
						ci32 d = Min( target - lg, eq );
						eq -= d;
						lg += d;
					}
					if( sm >= target && lg >= target ) 
						flag = true;

				}
				else if( p < q ) {
					ci32 sm_eq = sum[ mp[p] ] - 1;
					ci32 lg_eq = n - sum[ mp[q] - 1 ] - 1;
					if( sm_eq >= target && lg_eq >= target ) 
						flag = true;
				}
			}

			if( flag ) 
				printf( "TAK\n" );
			else 
				printf( "NIE\n" );
		}
	}
}
