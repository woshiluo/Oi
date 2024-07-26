/*
 * d.cpp 2024-07-11
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

const int N = 6e5 + 1e4;

struct Ops { int fu, fv; };
std::vector<Ops> ops;

struct Set {// {{{
	int set[N], size[N];
	i64 res[N];

	void init( int n ) {
		for( int i = 1; i <= n; i ++ ) {
			set[i] = i;
			size[i] = 1;
			res[i] = 0;
		}
	}

	i32 get_fa( int cur ) {
		if( set[cur] == cur ) 
			return set[cur];
		return get_fa( set[cur] );
	}

	i64 query( int cur ) {
		if( set[cur] == cur ) 
			return res[cur];
		return res[cur] + query( set[cur] );
	}

	void add( i32 val ) {
		res[ get_fa(1) ] += val;
	}

	void merge( ci32 u, ci32 v ) {
		i32 fu = get_fa(u);
		i32 fv = get_fa(v);
		if( fu == fv ) 
			return ;
		if( size[fu] < size[fv] ) 
			std::swap( fu, fv );

		// fu(fa) -> fv(son)

		set[fv] = set[fu];
		res[fv] -= res[fu];

		size[fu] += size[fv];

		ops.push_back( (Ops) { fu, fv } );
	}

	void reverse( ci32 idx ) {
		while( ops.size() > idx ) {
			auto [fu, fv] = ops.back(); ops.pop_back();
			res[fv] += res[fu];
			set[fv] = fv;

			size[fu] -= size[fv];
		}
	}
} set;// }}}


struct SegmentTree {// {{{
	struct Edge { i32 from, to; };
	struct Node {
		ci32 left, rig, mid;

		std::vector<Edge> edges;
		Node *son[2];

		Node(ci32 _left, ci32 _rig): left(_left), rig(_rig), mid( ( _left + _rig ) >> 1 ) {
			son[0] = son[1] = 0;
		}

		Node* get_son(int k) {
			if( son[k] ) 
				return son[k];
			if( k == 0 )
				son[0] = new Node( left, mid );
			else
				son[1] = new Node( mid + 1, rig );
			return son[k];
		}

		void add( ci32 from, ci32 to, Edge &cur ) {
			if( from <= left && rig <= to ) {
				edges.push_back(cur);
				return ;
			}

			if( from <= mid ) 
				get_son(0) -> add( from, to, cur );
			if( to > mid ) 
				get_son(1) -> add( from, to, cur );
		}

		void query() {
			ci32 idx = ops.size();

			for( auto &x: edges ) {
				set.merge( x.from, x.to );
			}

			if( left == rig ) 
				set.add(left);
			else {
				get_son(0) -> query();
				get_son(1) -> query();
			}

			set.reverse(idx);
		}
	};
	Node *rt;

	SegmentTree(int n) { rt = new Node( 1, n ); }
	void add( ci32 from, ci32 to, Edge cur ) { rt -> add( from, to, cur ); }

	void query() { rt -> query(); }
};// }}}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();

	SegmentTree sgt(n);
	set.init(n);
	for( int i = 1; i <= m; i ++ ) {
		ci32 a = read<i32>();
		ci32 b = read<i32>();
		ci32 l = read<i32>();
		ci32 r = read<i32>();

		sgt.add( l, r, (SegmentTree::Edge) { a, b } );
	}

	sgt.query();

	i64 res = 0;
	for( int i = 1; i <= n; i ++ ) {
		res ^= set.query(i);
	}

	printf( "%lld\n", res );
	
}
