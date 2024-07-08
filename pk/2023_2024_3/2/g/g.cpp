/*
 * g.cpp 2024-07-08
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

#include <tuple>
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

const int N = 1e6 + 1e4;

struct Set {
	int set[N];
	void init( ci32 n ) { for( int i = 0; i <= n; i ++ ) set[i] = i; }
	int get_fa( ci32 cur ) {
		if( set[cur] == cur )
			return cur;
		set[cur] = get_fa( set[cur] );
		return set[cur];
	}
	int& operator[]( const int cur ) { 
		return set[ get_fa(cur) ];
	}
} set;

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();
	ci32 k = read<i32>();

//	if( k < Min( n, m ) ) {
//		printf( "1\n");
//		return 0;
//	}

	std::vector<std::pair<i32, i32>> list(k);
	std::vector<i32> nums;
	for( auto &[x,y]: list ) {
		x = read<i32>() - 1;
		nums.push_back(x);
		if( x - 1 >= 0 )
			nums.push_back(x - 1);
		if( x + 1 < n )
			nums.push_back(x + 1);
		y = read<i32>() - 1;
	}

	std::sort( nums.begin(), nums.end() );
	nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );

	ci32 totx = nums.size();
	std::vector<std::vector<i32>> mp(totx);
	std::vector<std::vector<std::tuple<i32, i32, i32>>> segs(totx);
	set.init( k * 2 + totx );

	for( auto &[x,y]: list ) {
		x = std::lower_bound( nums.begin(), nums.end(), x ) - nums.begin();
		mp[x].push_back(y);
	}

	for( auto &p: mp ) {
		std::sort( p.begin(), p.end() );
		p.erase( std::unique( p.begin(), p.end() ), p.end() );
	}

	int seg_cnt = 0;
	for( int i = 0; i < totx; i ++ ) {
		// Gen segs
		int l = 0;
		for( auto &y: mp[i] ) {
			if( l == y ) {
				l = y + 1;
				continue;
			}
			{
				seg_cnt ++;
				segs[i].push_back( std::make_tuple( l, y - 1, seg_cnt ) );
			}
			l = y + 1;
		}
		if( mp[i].empty() || ( mp[i].back() != m - 1 && ( l <= m - 1 ) ) ) {
			seg_cnt ++;
			segs[i].push_back( std::make_tuple( l, m - 1, seg_cnt ) );
		}

		if( i == 0 )
			continue;

		int p0 = 0, p1 = 0;
		int s0 = segs[ i - 1 ].size(), s1 = segs[i].size();
		while( p0 < s0 && p1 < s1 ) {
			auto &[l0, r0, id0] = segs[ i - 1 ][p0];
			auto &[l1, r1, id1] = segs[i][p1];
			if( std::max( l0, l1 ) <= std::min( r0, r1 ) )
				set[id0] = set[id1];
			if( r0 < r1 )
				p0 ++;
			else 
				p1 ++;
		}
	}

	int res = 0;
	for( int i = 1; i <= seg_cnt; i ++ ) {
		if( set[i] == i ) {
			res ++;
		}
	}

	printf( "%d\n", res );
}
