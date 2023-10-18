/*
 * loj.3800.cpp 2023-09-27
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
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

struct ReadIn {
	int lastans;

	ReadIn() { lastans = 0; }

	void print( cint cur ) {
		lastans = cur;
		printf( "%d\n", cur );
	}

	int get_x() {
		return ( ( lastans + read<int>() - 1 ) % 39989 ) + 1;
	}
	int get_y() {
		return ( ( lastans + read<int>() - 1 ) % (int)(1e9) ) + 1;
	}
} readin;

struct SegmentTree {
	struct Segment {
		const int id;
		const double x1, y1, x2, y2;
		Segment( const int _id, const double _x1, const double _y1, const double _x2, const double _y2 ): id(_id), x1(_x1), y1(_y1), x2(_x2), y2(_y2) { }
		constexpr double get_value( cint cur ) {
			if( x1 == x2 ) 
				return Max( y1, y2 );
			return ( y2 - y1 ) / ( x2 - x1 ) * ( cur - x1 ) + y1;
		}
	};
	struct Node {
		cint left, rig, mid;
		Segment *seg;
		Node *son[2];
		Node( cint _left, cint _rig ): left(_left), rig(_rig), mid( ( _left + _rig ) >> 1 ) {
			seg = 0;
			son[0] = son[1] = 0;
		}
		~Node() {
		//	if( seg )
		//		delete seg;
			if( son[0] )
				delete son[0];
			if( son[1] )
				delete son[1];
		}

		constexpr Node* get_son( cint k ) {
			if( son[k] ) 
				return son[k];
			if( k == 0 ) 
				son[k] = new Node( left, mid );
			if( k == 1 ) 
				son[k] = new Node( mid + 1, rig );
			return son[k];
		}

		bool include ( const Segment &cur_seg ) {
			return cur_seg.x1 <= left && rig <= cur_seg.x2;
		}
	} *rt;

	SegmentTree( int n ) { rt = new Node(1, n); }
	~SegmentTree() { delete rt; }

	void add( Node *cur, Segment* seg ) {
		if( cur -> include( *seg ) ) {
			if( cur -> seg == 0 ) {
				cur -> seg = new Segment( seg -> id, seg -> x1, seg -> y1, seg -> x2, seg -> y2 );
				return ;
			}
			if( seg -> get_value( cur -> mid ) > cur -> seg -> get_value( cur -> mid ) ) {
				std::swap( seg, cur -> seg );
			}
			if( seg -> get_value( cur -> left ) > cur -> seg -> get_value( cur -> left ) )
				return add( cur -> get_son(0), seg );
			if( seg -> get_value( cur -> rig ) > cur -> seg -> get_value( cur -> rig ) )
				return add( cur -> get_son(1), seg );
			return ;
		}

		if( seg -> x1 <= cur -> mid ) 
			add( cur -> get_son(0), seg );
		if( seg -> x2 > cur -> mid ) 
			add( cur -> get_son(1), seg );
	}
	void add( Segment* seg ) { return add( rt, seg ); }

	Segment* query( Node *cur, cint val ) {
		if( cur -> left == cur -> rig && 
				cur -> left == val ) {
			return cur -> seg;
		}

		auto get_son_result = [&]() {
			if( val <= cur -> mid ) 
				return query( cur -> get_son(0), val );
			if( val > cur -> mid ) 
				return query( cur -> get_son(1), val );
			std::exit(-1);
		};
		Segment *res = get_son_result();
		if( res == 0 ) 
			return cur -> seg;
		if( cur -> seg == 0 ) 
			return res;

		if( res -> get_value(val) == cur -> seg -> get_value(val) ) 
			return ( res -> id > cur -> seg -> id )? res: cur -> seg;
		if( res -> get_value(val) < cur -> seg -> get_value(val) ) 
			return cur -> seg;
		else
			return res;
	}
	Segment* query( cint val ) { return query( rt, val ); }
};

int main() {
#ifdef woshiluo
	freopen( "loj.3800.in", "r", stdin );
	freopen( "loj.3800.out", "w", stdout );
#endif

	SegmentTree st(4e4);
	int T = read<int>();
	int seg_cnt = 0;
	while( T -- ) {
		cint op = read<int>();
		if( op == 0 ) {
			cint x = readin.get_x();
			const auto result = st.query(x);
			readin.print( result == 0? 0: result -> id );
		}
		if( op == 1 ) {
			int x1 = readin.get_x();
			int y1 = readin.get_y();
			int x2 = readin.get_x();
			int y2 = readin.get_y();
			if( x1 > x2 ) {
				std::swap( x1, x2 );
				std::swap( y1, y2 );
			}

			seg_cnt ++;
			SegmentTree::Segment* seg = new SegmentTree::Segment( seg_cnt, x1, y1, x2, y2 );
			st.add(seg);
		}
	}

}
