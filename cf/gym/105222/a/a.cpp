/*
 * a.cpp 2024-09-12
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

struct SegmentTree {
	struct Node {
		struct Data {
			i32 l, r, cnt;
			constexpr Data( bool valid = false ): l{valid}, r{valid}, cnt{valid} {}
			Data operator+ ( const Data &_b ) const {
				Data res;
				res.l = this -> l;
				res.r = _b.r;
				res.cnt = this -> cnt + _b.cnt;
				if( this -> r && _b.l ) 
					res.cnt --;
				return res;
			}
		};
		ci32 left, rig, mid;
		Data data;
		Node *son[2];

		Node( ci32 _left, ci32 _rig ): left(_left), rig(_rig), mid( ( _left + _rig ) >> 1 ), data(0) { son[0] = son[1] = 0; }

		Node* get_son( ci32 k ) { 
			if( son[k] ) 
				return son[k];
			if( k ) 
				son[k] = new Node( mid + 1, rig );
			else 
				son[k] = new Node( left, mid );
			return son[k];
		}
		void push_up() { data = get_son(0) -> data + get_son(1) -> data; }

		void init() {
			if( left == rig ) {
				data = true;
				return ;
			}
			get_son(0) -> init();
			get_son(1) -> init();

			this -> push_up();
		}

		void update( ci32 pos ) {
			if( left == rig ) {
				data = false;
				return ;
			}

			if( pos <= mid ) 
				get_son(0) -> update(pos);
			if( pos > mid ) 
				get_son(1) -> update(pos);

			this -> push_up();
		}

		Data sum( ci32 from, ci32 to ) {
			if( from <= left && rig <= to ) 
				return data;

			if( from <= mid && to > mid ) 
				return get_son(0) -> sum( from, to ) + get_son(1) -> sum( from, to );
			if( from <= mid ) 
				return get_son(0) -> sum( from, to );
			if( to > mid ) 
				return get_son(1) -> sum( from, to );

			return false;
		}
	};

	Node *rt;
	SegmentTree( ci32 n ) { rt = new Node( 1, n ); rt -> init(); }
	void update( ci32 pos ) { return rt -> update( pos ); }
	Node::Data sum( ci32 from, ci32 to ) { return rt -> sum( from, to ); }
};

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif


	ci32 n = read<i32>();

	std::vector<i32> a( n + 1 );
	SegmentTree sgt(n);

	i64 res = 0;
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<i32>();

		sgt.update( a[i] );
		if( a[i] > a[ i - 1 ] ) 
			res += sgt.sum( a[ i - 1 ] + 1, a[i] ).cnt;
	}

	printf( "%" PRId64 "\n", res );
	
}
