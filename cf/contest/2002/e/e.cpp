/*
 * e.cpp 2024-08-12
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

const int N = 3e5 + 1e4;

struct SegmentTree {
	i32 n;
	struct node { i64 max; } tree[ N << 2 ];

	inline void push_up( ci32 cur ) {  tree[cur].max = Max( tree[ cur << 1 ].max, tree[ cur << 1 | 1 ].max ); }

	void build( ci32 cur, ci32 left, ci32 rig ) {
		if( left == rig ) {
			tree[left].max = 0;
			return ;
		}
		ci32 mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		push_up( cur );
	}

	void init( ci32 _n ) {
		n = _n;
		build( 1, 1, n );
	}

	i64 query_max( ci32 from, ci32 to, ci32 cur, ci32 left, ci32 rig ) {
		if( from <= left && rig <= to ) { 
			return tree[cur].max;
		}

		ci32 mid = ( left + rig ) >> 1;
		i64 res = 0;
		if( from <= mid )
			chk_Max( res, query_max( from, to, cur << 1, left, mid ) );
		if( to > mid )
			chk_Max( res, query_max( from, to, cur << 1 | 1, mid + 1, rig ) );

		return res;
	}
	void query_set( ci32 from, ci32 to, i64 val, ci32 cur, ci32 left, ci32 rig ) {
		if( from != to ) 
			std::exit(-1);
		if( from <= left && rig <= to ) {
			tree[cur].max = val;
			return ;
		}

		ci32 mid = ( left + rig ) >> 1;
		if( from <= mid )
			query_set( from, to, val, cur << 1, left, mid );
		if( to > mid )
			query_set( from, to, val, cur << 1 | 1, mid + 1, rig );
		push_up(cur);
	}

	i64 max( ci32 from, ci32 to ) { return query_max( from, to, 1, 1, n ); }
	void set( ci32 from, ci32 to, i64 val ) { query_set( from, to, val, 1, 1, n ); }
} sgt;

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		sgt.init(n);
		std::map<i32, i32> mp;
		std::map<i32, i64> max_pos;
		for( int i = 1; i <= n; i ++ ) {
			ci64 a = read<i64>();
			ci64 b = read<i64>();
			if( mp.count(b) ) {
				ci32 la = mp[b];
				ci64 need_time = sgt.max( la + 1, i );
				ci64 la_a = max_pos[b];
				if( la_a >= need_time && a >= need_time ) 
					sgt.set( i, i, a + la_a - need_time );
				else 
					sgt.set( i, i, a );
			}
			else {
				max_pos[b] = a;
				sgt.set( i, i, a );
			}
			mp[b] = i;
			chk_Max( max_pos[b], sgt.max( i, i ) );
			printf( "%" PRId64 " ", sgt.max( 1, i ) );
		}
		printf( "\n" );
	}
}
