/*
 * loj.104.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

const int INF = 0x3f3f3f3f;

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
	for (; !isdigit(ch); ch = getchar())
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

struct Set {
	struct Node;
	struct NodePair;

	struct NodePair {
		Node *fir, *sec;
		inline int get_kind() { return fir -> priority > sec -> priority; }
		Node*& operator[] ( int idx ) {
			if( idx == 0 ) 
				return fir;
			else
				return sec;
		}
	};
	struct Node {
		int val, cnt, size;
		int priority;
		Node *son[2];


		Node( int _val ) { 
			val = _val;
			cnt = size = 0;
			priority = rand();
			son[0] = son[1] = 0;
		}
		bool operator< ( const Node &b ) const { return val < b.val; }
		inline void push_up() {
			size = son[0]? son[0] -> size: 0 +
				son[1]? son[1] -> size: 0 +
				cnt;
		}
		inline void add( int _val ) {
			cnt += _val;
			this -> push_up();
		}

		int find_max() {
			if( son[1] ) 
				return son[1] -> find_max();
			return val;
		}
		int find_min() {
			if( son[0] ) 
				return son[0] -> find_min();
			return val;
		}
		Node* merge( Node *rig ) {
			if( rig == 0 ) 
				return this;
			NodePair cur = (NodePair) { this, rig };
			int kind = cur.get_kind();

			if( cur[kind] -> son[ kind ^ 1 ] )
				cur[kind] -> son[ kind ^ 1 ] = 
					cur[kind] -> son[ kind ^ 1 ] -> merge( cur[ kind ^ 1 ] );

			cur[kind] -> push_up();
			return cur[kind];
		}
		NodePair split( int key ) {
			int kind = ( val > key );

			NodePair cur = (NodePair) { 0, 0 };
			cur[kind] = this;
			if( this -> son[ kind ^ 1 ] == 0 ) 
				return cur;

			NodePair nxt = this -> son[ kind ^ 1 ] -> split(key);
			this -> son[ kind ^ 1 ] = nxt[kind];
			cur[ kind ^ 1 ] = nxt[ kind ^ 1 ];

			return cur;
		}
	};

	Node *fa;
	Set() {
		fa = new Node(INF);
	}

	void update( int key, int val ) {
		Node *cur = fa;
		NodePair fpair = cur -> split(key);
		if( fpair[0] == 0 ) {
			fa = ( ( new Node(key) ) -> merge(fpair[1]) );
			return ;
		}
		NodePair spair = fpair[0] -> split(key - 1);

		if( spair[1] ) 
			spair[1] -> add(val);
		else {
			spair[1] = new Node(key);
			spair[1] -> add(val);
		}

		if( spair[1] -> cnt == 0 ) {
			delete spair[1];
			spair[1] = 0;
		}

		fa = spair[0] -> merge( spair[1] ) -> merge( fpair[1] );
	}

	int query_x( int x ) {
		int res = 0;
		Node *cur = fa;
		while( cur ) {
			if( cur -> val == x ) 
				return res + 1;
			if( cur -> val > x ) 
				cur = cur -> son[0];
			else {
				res += cur -> son[1]? cur -> son[1] -> size: 0 + 
					cur -> cnt;
				cur = cur -> son[1];
			}
		}
		return res + 1;
	}
	int query_rk_x( int x ) {
		int res = 0; 
		Node *cur = fa;
		while( cur ) {
			int rsize = cur -> son[0]? cur -> son[0] -> size: 0;
			if( res + rsize >= x )
				cur = cur -> son[0];
			else if( res + rsize + ( cur -> cnt ) >= x ) {
				return cur -> val;
			}
			else {
				res += rsize + ( cur -> cnt );
				cur = cur -> son[1];
			}
		}
		return 0;
	}

	int find_pre( int key ) {
		NodePair pair = fa -> split( key - 1 );
		int res = pair[0]? pair[0] -> find_max(): 0;
		fa = pair[0] -> merge( pair[1] );
		return res;
	}
	int find_nxt( int key ) {
		NodePair pair = fa -> split(key);
		int res = pair[1]? pair[1] -> find_min(): 0;
		fa = pair[0] -> merge( pair[1] );
		return res;
	}
} set;

int main() {
#ifdef woshiluo
	freopen( "loj.104.in", "r", stdin );
	freopen( "loj.104.out", "w", stdout );
#endif
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ){
		int opt = read<int>();
		int x = read<int>();
		if( opt == 1 ) {
			set.update( x, 1 );
		}
		else if( opt == 2 ) {
			set.update( x, -1 );
		}
		else if( opt == 3 ) {
			printf( "%d\n", set.query_x(x) );
		}
		else if( opt == 4 ) {
			printf( "%d\n", set.query_rk_x(x) );
		}
		else if( opt == 5 ) {
			printf( "%d\n", set.find_pre(x) );
		}
		else if( opt == 6 ) {
			printf( "%d\n", set.find_nxt(x) );
		}
	}
}
