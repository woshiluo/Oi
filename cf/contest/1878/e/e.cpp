/*
 * e.cpp 2023-09-27
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

struct SegmentTree {
	struct Node {
		cint left, rig, mid;
		int sum;
		Node* son[2];
		Node( cint _left, cint _rig ) :left(_left), rig(_rig), mid( ( _left + _rig ) >> 1 ) { 
			son[0] = son[1] = 0;
			sum = 0;
		}
		~Node() { 
			if( son[0] ) 
				delete son[0];
			if( son[1] ) 
				delete son[1];
		}
		Node* get_son( cint k ) {
			if( son[k] ) 
				return son[k];
			if( k == 0 ) 
				son[k] = new Node( left, mid );
			else
				son[k] = new Node( mid + 1, rig );

			return son[k];
		}

		void push_up() { sum = get_son(0) -> sum & get_son(1) -> sum; }
	} *rt;
	SegmentTree( cint n ) { rt = new Node( 1, n ); }
	~SegmentTree() { delete rt; }

	void set( Node *cur, cint pos, cint val ) {
		if( cur -> left == cur -> rig &&
				cur -> left == pos ) {
			cur -> sum = val;
			return ;
		}

		if( pos <= cur -> mid ) 
			set( cur -> get_son(0), pos, val );
		if( pos > cur -> mid ) 
			set( cur -> get_son(1), pos, val );

		cur -> push_up();
	}
	void set( cint pos, cint val ) { set( rt, pos, val ); }

	struct Respone { int sum, pos; };
	Respone try_extend( Node *cur, cint prefix, cint val ) {
		if( cur -> left == cur -> rig ) {
			if( ( prefix & cur -> sum ) >= val ) 
				return (Respone) { prefix & cur -> sum, cur -> left };
			else
				return (Respone) { prefix, cur -> left - 1 };
		}
		if( ( prefix & cur -> get_son(0) -> sum ) >= val ) 
			return try_extend( cur -> get_son(1), prefix & cur -> get_son(0) -> sum, val );
		else 
			return try_extend( cur -> get_son(0), prefix, val );

	}
	Respone get( Node* cur, cint pos, cint val ) {
		if( cur -> left == cur -> rig && cur -> left == pos ) {
			if( cur -> sum >= val )  
				return (Respone) { cur -> sum, pos };
			else
				return (Respone) { -1, -1 };
		}

		if( pos <= cur -> mid ) {
			const auto result = get( cur -> get_son(0), pos, val );
			if( result.sum == -1 ) 
				return result;
			if( result.pos < cur -> mid )
				return result;
			else {
				if( ( result.sum & cur -> get_son(1) -> sum ) >= val ) 
					return (Respone) { result.sum & cur -> get_son(1) -> sum, cur -> rig };
				else 
					return try_extend( cur -> get_son(1), result.sum, val );
			}
		}
		else {
			return get( cur -> get_son(1), pos, val );
		}
	}
	Respone get( cint pos, cint val ) { return get( rt, pos, val ); }
};

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		SegmentTree st(n);
		for( int i = 1; i <= n; i ++ ) 
			st.set( i, read<int>() );

		int q = read<int>();
		while( q -- ) {
			cint l = read<int>();
			cint k = read<int>();
			printf( "%d ", st.get( l, k ).pos );
		}
		printf( "\n" );
		
	}
	
}
