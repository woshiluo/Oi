/*
 * e.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

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
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 2e5 + 1e4;

struct Set {
	int set[N];
	void init( cint n ) { for( int i = 0; i <= n; i ++ ) set[i] = i; }
	int get_fa( cint cur ) {
		if( set[cur] == cur )
			return cur;
		set[cur] = get_fa( set[cur] );
		return set[cur];
	}
	int& operator[]( const int cur ) { 
		return set[ get_fa(cur) ];
	}
} set;

struct SegmentTree {
	int n;
	struct Node {
		int merged;
		std::vector<int> list;

		void merge( cint id ) {
			if( list.size() == 0 ) 
				return ;

			if( merged != -1 ) {
				set[merged] = set[id];
				return ;
			}
			for( auto &x: list ) {
				set[x] = set[id];
			}
			merged = set[id];
		}

		void clear() {
			merged = -1;
			list.resize(0);
			list.shrink_to_fit();
		}
	} tree[ N << 2 ];

	void build( cint cur, cint left, cint rig ) {/*{{{*/
		tree[cur].clear();
		if( left == rig ) 
			return ;

		cint mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
	}
	void init( cint _n ) { n = _n; build( 1, 1, n ); }/*}}}*/

	void add( cint from, cint to, cint id, cint cur, cint left, cint rig ) {/*{{{*/
		if( from <= left && rig <= to ) {
			tree[cur].list.push_back( id );
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		if( from <= mid ) 
			add( from, to, id, cur << 1, left, mid );
		if( to > mid ) 
			add( from, to, id, cur << 1 | 1, mid + 1, rig );
	}
	void add( cint from, cint to, cint id ) { add( from, to, id, 1, 1, n ); }/*}}}*/

	void merge( cint from, cint to, cint id, cint cur, cint left, cint rig ) {/*{{{*/
		tree[cur].merge(id);
		if( from <= left && rig <= to ) {
			return ;
		}

		cint mid = ( left + rig ) >> 1; 
		if( from <= mid ) 
			merge( from, to, id, cur << 1, left, mid );
		if( to > mid ) 
			merge( from, to, id, cur << 1 | 1, mid + 1, rig );
	}
	void merge( cint from, cint to, cint id ) { merge( from, to, id, 1, 1, n ); }/*}}}*/
} sgt[2];

int main() {
#ifdef woshiluo 
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>(); 
	while( T -- ) {
		cint n = read<int>();

		std::vector<int> nums;
		struct Node { int first, second, id; };
		std::vector<Node> col[2];

		for( int i = 1; i <= n; i ++ ) {
			cint c = read<int>(); cint l = read<int>(); cint r = read<int>();
			nums.push_back(l); nums.push_back(r);
			col[c].push_back( (Node) { l, r, i } );
		}

		std::sort( nums.begin(), nums.end() );
		nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );
		auto find = [&] ( cint cur ) { return std::lower_bound( nums.begin(), nums.end(), cur ) - nums.begin() + 1; };

		cint tot = nums.size() + 5;
		set.init(n); sgt[0].init( tot ); sgt[1].init( tot );
		for( auto &pair: col[0] ) {
			pair.first = find( pair.first );
			pair.second = find( pair.second );
		}
		for( auto &pair: col[1] ) {
			pair.first = find( pair.first );
			pair.second = find( pair.second );
		}

		for( auto &pair: col[0] ) {
			sgt[0].add( pair.first, pair.second, pair.id );
		}
		for( auto &pair: col[1] ) {
			sgt[1].add( pair.first, pair.second, pair.id );
		}
		for( auto &pair: col[0] ) {
			sgt[1].merge( pair.first, pair.second, pair.id );
		}
		for( auto &pair: col[1] ) {
			sgt[0].merge( pair.first, pair.second, pair.id );
		}

		int cnt = 0;
		for( int i = 1; i <= n; i ++ ) {
			cnt += ( set[i] == i );
		}
		printf( "%d\n", cnt );
	}
}
