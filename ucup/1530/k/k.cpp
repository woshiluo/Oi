/*
 * k.cpp 2024-10-16
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
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ( ch - '0' );
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
	struct Data {
		ci32 l, r;
		i64 cnt, sum, pop;
		Data( ci32 _l, ci32 _r ): l(_l), r(_r) {
			cnt = sum = pop = 0;
		}

		Data operator+ ( const Data &b );
	};
	struct Node {
		ci32 left, rig, mid;
		Node* son[2];
		Data data;

		Node( ci32 l, ci32 r ): left(l), rig(r), mid( ( l + r ) >> 1 ), data( l, r ) {
			son[0] = son[1] = 0;
		}

		Node* get_son( ci32 k ) {
			if( son[k] ) 
				return son[k];
			if( k == 0 ) 
				son[0] = new Node( left, mid );
			else 
				son[1] = new Node( mid + 1, rig );
			return son[k];
		}

		i64 find( ci32 l, ci32 r, ci32 cnt ) {
			if( mid < l ) 
				return get_son(1) -> find( l, r, cnt );
			if( r <= mid )
				return get_son(0) -> find( l, r, cnt );
			if( l == r ) 
				return data.sum;
			if( get_son(1) -> data.cnt >= cnt )
				return get_son(1) -> find( l, r, cnt );
			else {
				Data &rdata = get_son(1) -> data;
				return get_son(0) -> find( l, r, cnt - rdata.cnt + rdata.pop ) + rdata.sum;
			}
		}

	} *rt;

	i64 find( ci32 l, ci32 r, ci32 cnt ) { return rt -> find( l, r, cnt ); }
	void init( ci32 n ) { rt = new Node( 1, n ); }
} sgt;

SegmentTree::Data SegmentTree::Data::operator+(SegmentTree::Data const&b) {
	SegmentTree::Data res( this -> l, b.r );
	if( b.pop ) {
		if( b.pop >= this -> cnt ) {
			res.cnt = res.sum = 0;
			res.pop = b.pop - this -> cnt;
		}
		else {
			res.cnt = this -> cnt - b.pop;
			res.sum = this -> sum + b.sum - sgt.find( res.l, res.r, res.cnt );
			res.pop = 0;
		}
	}
	else {
		res.cnt = this -> cnt + b.cnt;
		res.pop = this -> pop + b.pop;
		res.sum = this -> sum + b.sum;
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "k.in", "r", stdin );
	freopen( "k.out", "w", stdout );
#endif

	
}
