/*
 * d.cpp 2024-03-15
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

#include <iterator>
#include <map>
#include <set>
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
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::deque<i32> b;
		std::deque<std::pair<i32, i32>> a;
		std::map<i32, i32> pool;
		int mex = 0;
		i64 res = 0, ans = 0;
		for( int i = 0; i < n; i ++ ) {
			ci32 x = read<i32>();
			pool[x] ++;
			b.push_back(x);
			while( pool[mex] ) 
				mex ++;
			res += mex;
			if( a.size() && mex == a.back().first )
				a.back().second ++;
			else 
				a.push_back( std::make_pair( mex, 1 ) );
		}
		chk_Max( ans, res );
		for( int i = 0; i < n; i ++ ) {
			b.push_back( b.back() );
			res -= a.front().first;
			a.front().second --;
			if( a.front().second == 0 )
				a.pop_front();
			i32 count = 0;
			while( a.size() && a.back().first >= b.front() ) {
				res -= 1LL * a.back().first * a.back().second;
				count += a.back().second;
				a.pop_back();
			}
			res += 1LL * b.front() * count;
			a.push_back( std::make_pair( b.front(), count ) );
			res += n;
			a.push_back( std::make_pair( n, 1 ) );
			b.pop_front();
			chk_Max( ans, res );
		}
		printf( "%lld\n", ans );
	}
}
