/*
 * e.cpp 2024-04-13
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

const int MAXA = 1e5 + 1e2;

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	ci32 n = read<i32>();
	std::vector<i32> a(n);
	for( auto &x: a )
		x = read<i32>();

	i64 res = 0;
	i32 maxa = *std::max_element( a.begin(), a.end() );
	std::vector<i32> lst(n);
	for( int i = 0; i < n; i ++ ) {
		if( i == 0 ) {
			lst[i] = a[i];
			res += a[i];
			continue;
		}
		if( a[i] > lst[ i - 1 ] ) {
			res += a[i] - lst[ i - 1 ];
		}
		lst[i] = a[i];
	}

	std::vector<i32> list[MAXA];
	for( int i = 0; i < n; i ++ ) {
		a[i] -= 1;
		for( int l = 1, r = 0; l < MAXA; l = r + 1) {
			list[l].push_back(i);
			if( a[i] / l == 0 ) 
				break;
			r = a[i] / ( a[i] / l );
		}
		a[i] += 1;
	}

	std::vector<i32> b = a;
	int p0 = 0;
	for( int i = 1; i <= maxa; i ++ ) {
		for( auto &p1: list[i] ) {
			if( p1 == 0 ) {
				res -= b[0];
			}
			if( p1 - 1 >= 0 && b[p1] > lst[ p1 - 1 ] ) {
				res -= b[p1] - lst[ p1 - 1 ];
			}
			if( p1 + 1 < n && b[p1 + 1] > lst[p1] ) {
				res -= b[p1 + 1] - lst[p1];
			}
			b[p1] = ( a[p1] + i - 1 ) / i;
			lst[p1] = b[p1];
			if( p1 == 0 ) {
				res += b[0]; }
			if( p1 - 1 >= 0 && b[p1] > lst[ p1 - 1 ] ) {
				res += b[p1] - lst[ p1 - 1 ];
			}
			if( p1 + 1 < n && b[p1 + 1] > lst[p1] ) {
				res += b[p1 + 1] - lst[p1];
			}
		}
		printf( "%lld ", res );
	}
}
