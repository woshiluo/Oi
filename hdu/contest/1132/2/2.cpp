/*
 * 2.cpp 2024-08-16
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

std::vector<i32> a, b;

struct SegmentTree {// {{{
	struct Node {
		struct Data {
			int min, max;
			int min_pos, max_pos;

			Data(): min{INT32_MAX}, max{0}, min_pos{0}, max_pos{0} {}
			Data( ci32 pos, ci32 val ) {
				min = max = val;
				min_pos = max_pos = pos;
			}

			Data operator+ ( const Data &_b ) const {
				Data res;
				res.min = Min( min, _b.min );
				res.max = Max( max, _b.max );

				if( res.min == min ) 
					res.min_pos = min_pos;
				if( res.max == max ) 
					res.max_pos = max_pos;
				if( res.min == _b.min ) 
					res.min_pos = _b.min_pos;
				if( res.max == _b.max ) 
					res.max_pos = _b.max_pos;

				return res;
			}
		};
		ci32 left, rig, mid;
		Data data;
		Node *son[2];

		Node( ci32 _l, ci32 _r ): left{_l}, rig{_r}, mid{ ( _l + _r ) >> 1 }, data(), son{ 0, 0 } {}
		~Node() {
			if( son[0] ) 
				delete son[0];
			if( son[1] ) 
				delete son[1];
		}

		constexpr Node* get_son( ci32 k ) {
			if( son[k] ) 
				return son[k];
			if( k == 0 ) 
				son[0] = new Node( left, mid );
			else 
				son[1] = new Node( mid + 1, rig );
			return son[k];
		}

		void push_up() {
			const Node* p1 = get_son(0);
			const Node* p2 = get_son(1);


			data = p1 -> data + p2 -> data;
		}

		void change( ci32 pos, ci32 val ) {
			if( left == rig ) {
				data = Data( pos, val );
				return ;
			}

			if( pos <= mid ) 
				get_son(0) -> change( pos, val );
			if( pos > mid ) 
				get_son(1) -> change( pos, val );

			this -> push_up();
		}

		Data query( ci32 from, ci32 to ) {
			if( from <= left && rig <= to ) {
				return data;
			}

			Data res;
			if( from <= mid ) 
				res = res + get_son(0) -> query( from, to );
			if( to > mid ) 
				res = res + get_son(1) -> query( from, to );

			return res;
		}
	};

	Node *rt;

	SegmentTree( ci32 n ) { rt = new Node( 1, n ); }
	~SegmentTree() { delete rt; }

	void change( ci32 pos, ci32 val ) { rt -> change( pos, val ); }
	Node::Data query( ci32 from, ci32 to ) { return rt -> query( from, to ); }
};// }}}
  
const int N = 1e5 + 1e4;
  
struct Edge {
	i32 to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

int size[N], mson[N], dep[N], fa[N];
void dfs( ci32 cur, ci32 la ) {
	dep[cur] = dep[la] + 1; size[cur] = 1;
	fa[cur] = la; mson[cur] = 0;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, cur );
		size[cur] += size[ e[i].to ];

		if( size[ e[i].to ] > size[ mson[cur] ] ) 
			mson[cur] = e[i].to;
	}
}

int idx;
int top[N], dfn[N];
void dfs1( ci32 cur, ci32 la ) {
	idx ++;
	dfn[cur] = idx;
	if( mson[cur] ) {
		top[ mson[cur] ] = top[cur];
		dfs1( mson[cur], cur );
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == mson[cur] || e[i].to == la ) 
			continue;
		top[ e[i].to ] = e[i].to;
		dfs1( e[i].to, cur );
	}
}

int get_lca( i32 from, i32 to ) {
	while( top[from] != top[to] ) {
		if( dep[ top[from] ] < dep[ top[to] ] )
			std::swap( from, to );

		from = fa[ top[from] ];
	}
	return dep[from] < dep[to]? from: to;
}

bool query( SegmentTree &sgt, i32 from, i32 to, ci32 left, ci32 rig ) {
	SegmentTree::Node::Data res;
	while( top[from] != top[to] ) {
		if( dep[ top[from] ] < dep[ top[to] ] )
			std::swap( from, to );

		res = res + sgt.query( dfn[ top[from] ], dfn[from] );
		from = fa[ top[from] ];
	}

	if( dep[from] > dep[to] ) 
		std::swap( from, to );
	res = res + sgt.query( dfn[from], dfn[to] );

	return res.min == left && res.max == rig;
}

int main() {
#ifdef woshiluo
	freopen( "2.in", "r", stdin );
	freopen( "2.out", "w", stdout );
#endif

	i32 T = read<i32>();

	while( T -- ) {
		ci32 n = read<i32>();

		idx = 0;
		ecnt = 0;
		memset( ehead, 0, sizeof(ehead[0]) * ( n + 5 ) );

		std::vector<i32> p( n + 1 ), rev( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			p[i] = read<i32>();
		}

		for( int i = 1; i < n; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			add_edge( u, v );
			add_edge( v, u );
		}

		top[1] = 1;
		dfs( 1, 0 );
		dfs1( 1, 0 );
		
		std::vector<std::set<i32>> set( n + 1 );
		SegmentTree dep_seg(n), hld_seg(n);

		auto set_node = [&]( ci32 cur ) {
			dep_seg.change( p[cur], dep[cur] );
			hld_seg.change( dfn[cur], p[cur] );
			rev[ p[cur] ] = cur;
		};
		for( int i = 1; i <= n; i ++ ) {
			set_node(i);
		}
		for( int i = 1; i <= n; i ++ ) 
			set[ dep[i] ].insert( p[i] );

		const auto op2 = [&]() {
			ci32 l = read<i32>();
			ci32 r = read<i32>();
			const auto data = dep_seg.query( l, r );
			const auto lca = rev[data.min_pos];
			const auto y = rev[data.max_pos];
			// Check unique lca
			{
				auto lca_st = set[ dep[lca] ].lower_bound(l);
				lca_st ++;
				if( lca_st != set[ dep[lca] ].end() && *lca_st <= r )
					return false;
			}
			// Get dep[x]
			const auto tar_dep = r - l - dep[y] + dep[lca] * 2;
			if( tar_dep < 1 ) 
				return false;
			if( tar_dep == dep[lca] ) {
				return query( hld_seg, lca, y, l, r );
			}
			{
				auto x_p = set[ tar_dep ].lower_bound(l);
				if( x_p == set[ tar_dep ].end() )
					return false;
				else {
					const auto x_st = x_p;
					x_p ++; const auto x_st_1 = x_p;
					if( x_st_1 == set[ tar_dep ].end() ) 
						return false;
					if( get_lca( *x_st, y ) == lca ) {
						return query( hld_seg, *x_st, y, l, r );
					}
					else if( get_lca( *x_st_1, y ) == lca ) {
						return query( hld_seg, *x_st_1, y, l, r );
					}
				}
			}
			return false;
		};
		ci32 m = read<i32>();
		for( int _ = 1; _ <= m; _ ++ ) {
			ci32 op = read<i32>();
			if( op == 1 ) {
				ci32 x = read<i32>();
				ci32 y = read<i32>();
				if( x == y ) 
					continue;
				set[ dep[x] ].erase( p[x] );
				set[ dep[y] ].erase( p[y] );

				std::swap( p[x], p[y] );
				
				set[ dep[x] ].insert( p[x] );
				set[ dep[y] ].insert( p[y] );

				set_node(x);
				set_node(y);
			}
			if( op == 2 ) {
				if( op2() ) 
					printf( "Yes\n" );
				else
					printf( "No\n" );
			}
		}
	}
}
