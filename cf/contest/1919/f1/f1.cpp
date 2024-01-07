/*
 * f1.cpp 2024-01-07
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

const int N = 5e5 + 1e4;


struct SegmentTree {/*{{{*/
	struct Node {/*{{{*/
		ci32 left, rig, mid;
		int sum, lazy;
		Node *son[2];
		Node( ci32 _left, ci32 _rig, ci32 _sum = 0 ): left(_left), rig(_rig), mid( ( _left + _rig ) >> 1 ), sum(_sum) { son[0] = son[1] = 0; }

		void push_up() {
			sum = 0;
			if( son[0] ) 
				sum += son[0] -> sum;
			if( son[1] ) 
				sum += son[1] -> sum;
		}

		Node* get_son( bool kind ) {
			if( !son[kind] ) {
				if( kind == false ) 
					son[kind] = new Node( left, mid );
				else
					son[kind] = new Node( mid + 1, rig );
			}
			return son[kind];
		}
		bool contained_by( ci32 from, ci32 to ) { return from <= left && rig <= to; }
		bool contained_by( ci32 pos ) { return contained_by( pos, pos ); }
	};/*}}}*/
	Node *rt;

	SegmentTree( ci32 n = N ) :rt( new Node( 1, n ) ) {}

	void add( ci32 from, ci32 to, ci32 val, Node *cur ) {
		if( cur -> contained_by(from, to) ){
			cur -> sum += val * ( to - from + 1 );;
			return ;
		} 

		cur -> push_down();
		ci32 mid = cur -> mid;
		if( pos <= mid ) 
			add( pos, val, cur -> get_son(0) );
		if( pos > mid ) 
			add( pos, val, cur -> get_son(1) );

		cur -> push_up();
	}
	void add( ci32 pos, ci32 val ) { return add( pos, val, rt ); }

	int sum( ci32 from, ci32 to, Node *cur ) {
		if( cur -> contained_by( from, to ) ) {
			return cur -> sum;
		}
		
		int res = 0;
		ci32 mid = cur -> mid;
		if( from <= mid ) 
			res += sum( from, to, cur -> get_son(0) );
		if( to > mid ) 
			res += sum( from, to, cur -> get_son(1) );

		return res;
	}
	int sum( ci32 from, ci32 to ) { 
		if( to < from ) 
			return 0;
		return sum( from, to, rt );
	}
} sgts[N][2];/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "f1.in", "r", stdin );
	freopen( "f1.out", "w", stdout );
#endif

	
}
