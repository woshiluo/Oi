/*
 * g.cpp 2024-07-21
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

const i32 mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( long long _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

using pii = std::pair<i32, i32>;

const int N = 3e5 + 1e4;

bool blocked[N];

std::vector<i32> nodes[N];
std::vector<pii> edges[N];
std::vector<i32> eid[N];


struct Ops { int fu, fv; };
std::vector<Ops> ops;
struct Set {// {{{
	int set[N << 1], size[N << 1];

	void init( int n ) {
		ops.resize(0);
		for( int i = 0; i <= n; i ++ ) {
			set[i] = i;
			size[i] = 1;
		}
	}

	i32 get_fa( int cur ) {
		if( set[cur] == cur ) 
			return set[cur];
		return get_fa( set[cur] );
	}


	void merge( ci32 u, ci32 v ) {
		i32 fu = get_fa(u);
		i32 fv = get_fa(v);
		if( fu == fv ) 
			return ;
		if( size[fu] < size[fv] ) 
			std::swap( fu, fv );

		set[fv] = set[fu];

		size[fu] += size[fv];

		ops.push_back( (Ops) { fu, fv } );
	}

	void reverse( ci32 idx ) {
		while( (int)ops.size() > idx ) {
			auto [fu, fv] = ops.back(); ops.pop_back();
			set[fv] = fv;

			size[fu] -= size[fv];
		}
	}
} set;// }}}
	  
struct SegmentTree {// {{{
	struct Edge { i32 id, from, to, diff; };
	struct Node {
		ci32 left, rig, mid;

		std::vector<Edge> edges;
		Node *son[2];

		Node(ci32 _left, ci32 _rig): left(_left), rig(_rig), mid( ( _left + _rig ) >> 1 ) {
			son[0] = son[1] = 0;
		}
		~Node() {
			if( son[0] ) 
				delete(son[0]);
			if( son[1] ) 
				delete(son[1]);
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

		void query( ci32 n, ci32 test_node, std::vector<bool> &flagged ) {
			ci32 idx = ops.size();

			for( auto &x: edges ) {
				if( x.diff ) {
					set.merge( x.from + n, x.to );
					set.merge( x.from, x.to + n );
				}
				else {
					set.merge( x.from + n, x.to + n );
					set.merge( x.from, x.to );
				}
			}

			if( left == rig ) {
				if( set.get_fa(test_node) == set.get_fa(test_node + n) ) 
					flagged[ left - 1 ] = true;
			}
			else {
				get_son(0) -> query(n, test_node, flagged);
				get_son(1) -> query(n, test_node, flagged);
			}

			set.reverse(idx);
		}
	};
	Node *rt;

	~SegmentTree() { delete(rt); }
	SegmentTree(int n) { rt = new Node( 1, n ); }
	void add( ci32 from, ci32 to, Edge cur ) { 
		if( to < from ) 
			return ;
		rt -> add( from, to, cur );
	}

	void query( ci32 n, ci32 test_node, std::vector<bool> &flagged ) { rt -> query(n, test_node, flagged); }
};// }}}

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();

	{// {{{
		std::vector<i32> p( n - 1 );
		for( auto &x: p )
			x = read<i32>();
	}// }}}
	
	set.init(n);

	std::vector<std::pair<i32, i32>> list;
	for( int i = 1; i <= m; i ++ ) {
		ci32 u = read<i32>();
		ci32 v = read<i32>();

		list.emplace_back( u, v );
		set.merge( u, v );
	}

	i32 scc_cnt = 0;

	for( int i = 1; i <= n; i ++ ) {
		scc_cnt += ( set.get_fa(i) == i );
	}

	for( int i = 0; i < m; i ++ ) {
		const auto &[u, v] = list[i];
		ci32 fu = set.get_fa(u);
		nodes[fu].push_back(u);
		nodes[fu].push_back(v);
		edges[fu].push_back(list[i]);
		eid[fu].push_back( i + 1 );
	}

	set.init( n * 2 + 2 );

	for( int p = 1; p <= n; p ++ ) {
		if( edges[p].size() == 0 ) 
			continue;

		std::sort( nodes[p].begin(), nodes[p].end() );
		ci32 size = edges[p].size();

		std::vector<bool> flagged( size, false );

		SegmentTree sgt(size);
		for( int i = 0; i < size; i ++ ) {
			const auto &[u, v] = edges[p][i];
			SegmentTree::Edge p1 = { i + 1, u, v, 0 };
			SegmentTree::Edge p2 = { i + 1, u, v, 1 };
			sgt.add( 1, i + 1, p2 );
			sgt.add( i + 2, size, p1 );
		}

		sgt.query( n, nodes[p][0], flagged );

		i32 la = 0;
		for( int i = 0; i < size; i ++ ) {
			if( flagged[i] ) {
				for( int j = la + 1; j <= eid[p][i]; j ++ ) {
					blocked[j] |= true;
				}
			}

			la = eid[p][i];
		}
	}

	const ModInt once = pow( (ModInt)2, scc_cnt - 1 );
	ModInt res = once;
	for( int j = 1; j <= m; j ++ ) {
		if( blocked[j] ) 
			continue;
		res += once;
	}

	res.output();
}
