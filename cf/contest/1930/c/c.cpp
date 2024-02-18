/*
 * c.cpp 2024-02-18
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
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::map<i32, std::vector<i32>> min;
		std::map<i32, i32> cnt;
		for( int i = 1; i <= n; i ++ ) {
			ci32 cur = read<i32>();
			ci32 val = cur + i;
			cnt[val] ++;
			min[val].push_back(cur+1);
		}
		std::vector<i32> list;
		for( auto &[ fir, _ ]: cnt ) 
			list.push_back(fir);
		std::reverse( list.begin(), list.end() );
		int nxt = list[0];
		std::vector<i32> res;
		std::map<i32, i32> less;
		ci32 size = list.size();
		for( int j = 0; j < size; j ++ ) {
			ci32 key = list[j];
			chk_Min( nxt, key );
			auto &mins = min[key];
			for( auto &x: mins ) 
				less[x] ++;
			while( less.size() ) {
				if( j + 1 < size && nxt == list[ j + 1 ] )
						break;
				if( less.rbegin() -> first <= nxt ) {
					res.push_back(nxt);
					nxt --;
				}
				less.rbegin() -> second --;
				if( less.rbegin() -> second == 0 ) 
					less.erase( less.rbegin() -> first ) ;
			}
		}
		for( auto &x: res ) 
			printf( "%d " , x );
		printf( "\n" );
	}
}
