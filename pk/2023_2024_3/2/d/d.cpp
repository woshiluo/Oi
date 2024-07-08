/*
 * d.cpp 2024-07-08
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

std::map<i32, char> mp;
std::map<i32, i32> eqs, eqn;
std::map<i32, i32> fa;
std::set<i32> set;

int dfs( int cur ) {
	auto p2 = eqs.upper_bound(cur);
	if( p2 == eqs.begin() ) 
		return cur;

	p2 --;
	auto p1 = p2;
	p2 ++;

	if( p1 -> second == 0 ) 
		return cur;

	i32 nxt = p1 -> second + ( cur - p1 -> first );
	if( nxt >= p1 -> first ) {
		ci32 diff = cur - nxt;
		ci32 p = ( cur - p1 -> first ) / diff;
		i32 rnxt = cur - p * diff;
		while( rnxt >= p1 -> first )
			rnxt -= diff;
		nxt = rnxt;
	}
	return dfs(nxt);
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 a = read<i32>();
	ci32 b = read<i32>();
	ci32 q = read<i32>();
	
	std::vector<std::pair<i32, char>> list;
	for( int i = 1; i <= a; i ++ ) {
		ci32 x = read<i32>();
		static char buf[8];
		scanf( "%s", buf );
		list.push_back( std::make_pair( x, buf[0] ) );
	}
	for( int i = 1; i <= b; i ++ ) {
		ci32 y = read<i32>();
		ci32 h = read<i32>();
		eqs[y] = h;
	}

	for( auto &[x, p]: list ) {
		mp[ dfs(x) ] = p;
	}

	for( int _ = 0; _ < q; _ ++ ) {
		ci32 x = read<i32>();
		ci32 r = dfs(x);
		if( mp.count(r) ) 
			printf( "%c", mp[r] );
		else
			printf( "?" );
	}
}
