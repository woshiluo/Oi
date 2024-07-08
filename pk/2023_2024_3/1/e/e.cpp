/*
 * e.cpp 2024-07-07
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

const int N = 2e5 + 10;

struct SegmentTree {
	struct Node {
		std::set<i32> set;
	} tree[ N << 2 ];
	int n;
	void init( int _n ) {
		n = _n;
	}

	int query( ci32 pos, ci32 id, ci32 cur, ci32 left, ci32 rig ) {
		i32 min = N;
		if( !tree[cur].set.empty() && *tree[cur].set.begin() != id )
			chk_Min( min, *tree[cur].set.begin() );
		else if( tree[cur].set.size() > 1 ) {
			auto p = tree[cur].set.begin();
			p ++;
			chk_Min( min, *p );
		}

		if( left == rig )
			return min;

		ci32 mid = ( left + rig ) >> 1;
		if( pos <= mid ) 
			return Min( min, query( pos, id, cur << 1, left, mid ) );
		if( pos > mid ) 
			return Min( min, query( pos, id, cur << 1 | 1, mid + 1, rig ) );

		return min;
	}
	int query( ci32 pos, ci32 id ) { return query( pos, id, 1, 1, n ); }
	void add( ci32 from, ci32 to, ci32 id, ci32 cur, ci32 left, ci32 rig ) {
		if( from <= left && rig <= to )  {
			tree[cur].set.insert(id);
			return ;
		}
		ci32 mid = ( left + rig ) >> 1;
		if( from <= mid )
			add( from, to, id, cur << 1, left, mid );
		if( to > mid )
			add( from, to, id, cur << 1 | 1, mid + 1, rig );
	}
	void add( ci32 from, ci32 to, ci32 id ) { return add( from, to, id, 1, 1, n ); }
	void remove( ci32 from, ci32 to, ci32 id, ci32 cur, ci32 left, ci32 rig ) {
		if( from <= left && rig <= to )  {
			tree[cur].set.erase(id);
			return ;
		}
		ci32 mid = ( left + rig ) >> 1;
		if( from <= mid )
			remove( from, to, id, cur << 1, left, mid );
		if( to > mid )
			remove( from, to, id, cur << 1 | 1, mid + 1, rig );
	}
	void remove( ci32 from, ci32 to, ci32 id ) { return remove( from, to, id, 1, 1, n ); }
} sgt;

struct Node {
	i32 x, y, z;
	int type, id;
	// 0 add
	// 1 normal
	// 2 sub
};

std::vector<Node> cubs;

i32 global_ans, dx, dy, dz;

void work( int yl, int yr, std::vector<Node> &nodes ) {
	ci32 mid = ( yl + yr ) >> 1;
	std::vector<Node> lnodes, rnodes;
	for( auto &node: nodes ) {
		if( node.type == 1 ) {
			ci32 id = sgt.query(node.z, node.id);
			chk_Min( global_ans, Max( node.id, id ) );
			if( node.y <= mid ) 
				lnodes.push_back(node);
			else
				rnodes.push_back(node);
		}
		else {
			auto &p1 = cubs[node.id - 1];
			auto &p2 = p1;
			p2.x += dx;
			p2.y += dy;
			p2.z += dz;
			if( p1.y <= yl && yr <= p2.y ) {
				if( node.type == 0 ) {
					sgt.add(p1.z, p2.z, p1.id);
				}
				else {
					sgt.remove(p1.z, p2.z, p1.id);
				}
			}
			else {
				if( p2.y > mid )
					rnodes.push_back(node);
				if( p1.y <= mid )
					lnodes.push_back(node);
			}
		}
	}
	nodes.resize(0);
	nodes.shrink_to_fit();
	if( yl != yr ) {
		work( yl, mid, lnodes ); work( mid + 1, yr, rnodes );
	}
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	std::vector<i32> numx, numy, numz;
	ci32 n = read<i32>();
	dx = read<i32>();
	dy = read<i32>();
	dz = read<i32>();
	std::vector<Node> nodes;
	for( int i = 1; i <= n; i ++ ) {
		ci32 x = read<i32>();
		ci32 y = read<i32>();
		ci32 z = read<i32>();
		numx.push_back(x); numx.push_back(x + dx);
		numy.push_back(y); numy.push_back(y + dy);
		numz.push_back(z); numz.push_back(z + dz);

		nodes.push_back( (Node){ x, y, z, 0, i } );
		nodes.push_back( (Node){ x + dx, y + dy, z + dz, 2, i } );

		cubs.push_back( (Node){ x, y, z, 0, i } );

		for( int p1 = 0; p1 <= 1; p1 ++ ) {
			for( int p2 = 0; p2 <= 1; p2 ++ ) {
				for( int p3 = 0; p3 <= 1; p3 ++ ) {
					nodes.push_back( (Node){ x + dx * p1, y + dy * p2, z + dz * p3, 1, i } );
				}
			}
		}
	}
	
// {{{
	std::sort( numx.begin(), numx.end() );
	std::sort( numy.begin(), numy.end() );
	std::sort( numz.begin(), numz.end() );

	numx.erase( std::unique( numx.begin(), numx.end() ), numx.end() );
	numy.erase( std::unique( numy.begin(), numy.end() ), numy.end() );
	numz.erase( std::unique( numz.begin(), numz.end() ), numz.end() );

	auto find = []( std::vector<i32> &nums, ci32 x ) { 
		return std::lower_bound( nums.begin(), nums.end(), x ) - nums.begin() + 1;
	};

	for( auto &[x, y, z, _1, _2]: nodes ) {
		x = find( numx, x );
		y = find( numy, y );
		z = find( numz, z );
	}

	for( auto &p1: cubs ) {
		p1.x = find( numx, p1.x );
		p1.y = find( numy, p1.y );
		p1.z = find( numz, p1.z );
	}


// }}}

	global_ans = n + 1;
	sgt.init( numz.size() );

	std::sort( nodes.begin(), nodes.end(), []( const auto &_a, const auto &_b ) { 
		if( _a.x == _b.x ) {
			if( _a.type == _b.type )
				return _a.id < _b.id;
			return _a.type < _b.type;
		}
		return _a.x < _b.x;
	});
	work(1, numy.size(), nodes);


	if( global_ans > n )
		printf( "0" );
	else
		printf( "%d\n", global_ans );
}
