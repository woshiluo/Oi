/*
 * loj.2720.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <map>
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

const int N = 1e6 + 1e5;

struct SegmentTree {/*{{{*/
	struct Node {/*{{{*/
		cint left, rig;
		int max;
		Node *son[2];

		Node* get_son( cint p ) {/*{{{*/
			cint mid = get_mid();
			if( !son[p] ) {
				if( p == 0 )
					son[p] = new Node( left, mid );
				if( p == 1 )
					son[p] = new Node( mid + 1, rig );
			}
			return son[p];
		}
		void push_up() {
			if( son[0] ) {
				chk_Max( max, son[0] -> max ); 
			}
			if( son[1] ) {
				chk_Max( max, son[1] -> max ); 
			}
		}/*}}}*/

		int get_mid() const { return ( left + rig ) >> 1; }

		Node( cint _left, cint _rig, cint _max = 0 ): left(_left), rig(_rig)  {
			max = _max; son[0] = son[1] = 0;
		}

		void insert( cint pos ) {/*{{{*/
			if( left == rig && left == pos ) {
				max = pos;
				return ;
			}

			cint mid = get_mid();
			if( pos <= mid ) 
				get_son(0) -> insert(pos);
			if( pos > mid ) 
				get_son(1) -> insert(pos);

			push_up();
		}/*}}}*/

		int get_max( cint from, cint to ) {/*{{{*/
			if( from <= left && rig <= to ) {
				return max;
			}

			cint mid = get_mid();
			int res = 0;
			if( from <= mid && son[0] )
				chk_Max( res, son[0] -> get_max( from, to ) );
			if( to > mid && son[1] )
				chk_Max( res, son[1] -> get_max( from, to ) );

			return res;
		}/*}}}*/
	};/*}}}*/

	Node *rt;

	void init( cint n ) { rt = new Node( 1, n ); }

	void insert( cint pos ) { rt -> insert(pos); }
	int max( cint from, cint to ) { return rt -> get_max( from, to ); }
};/*}}}*/

SegmentTree::Node* merge( SegmentTree::Node * lcur, SegmentTree::Node* rcur ) {/*{{{*/
	if( !rcur && lcur ) 
		return lcur;
	if( rcur && !lcur ) 
		return rcur;
	if( !lcur && !rcur ) 
		return 0;

	SegmentTree::Node *cur = new SegmentTree::Node( lcur -> left, lcur -> rig );
	cur -> max = Max( lcur -> max, rcur -> max );

	cur -> son[0] = merge( lcur -> son[0], rcur -> son[0] );
	cur -> son[1] = merge( lcur -> son[1], rcur -> son[1] );

	cur -> push_up();

	return cur;
}/*}}}*/

int f1[N], f2[N];
SegmentTree sgt[N];

struct Graph {/*{{{*/
	struct Edge {
		int to, next;
	} e[N];
	int ehead[N], ecnt;

	void init( cint n ) {
		ecnt = 0;
		for( int i = 0; i <= n; i ++ ) 
			ehead[i] = 0;
	}
	void add_edge( cint cur, cint to ) {
		ecnt ++;
		e[ecnt].to = to;
		e[ecnt].next = ehead[cur];
		ehead[cur] = ecnt;
	}

	 ll dfs( cint cur, cint la ) {
		 ll res = 0;
		 for( int i = ehead[cur]; i; i = e[i].next ) {
			 res += dfs( e[i].to, cur );
			 chk_Max( f1[cur], f1[ e[i].to ] );
		 }

		 chk_Min( f1[cur], f2[cur] );
		 res += f2[cur] - f2[la];
		 res -= Max( f1[cur] - f2[la], 0 );

		 return res;
	 }

	 void build_sgt( cint cur, cint size ) {
		 bool has_val = false;
		 for( int i = ehead[cur]; i; i = e[i].next ) {
			 build_sgt( e[i].to, size );
			 if( has_val ) 
				 sgt[cur].rt = merge( sgt[cur].rt, sgt[ e[i].to ].rt );
			 else {
				 has_val = true;
				 sgt[cur].rt = sgt[ e[i].to ].rt;
			 }
		 }

		 if( !has_val ) {
			 sgt[cur].init(size);
			 sgt[cur].insert( f1[cur] );
		 }
	 }
};/*}}}*/

bool vis[N];

struct SuffixAutoMaton {/*{{{*/
	int cnt;

	struct Node {
		int id, len, val;
		Node *link;
		std::map<char, Node*> nxt;

		Node( int &cnt, cint _len = 0, Node* _link = 0, cint _val = 0 ) {
			cnt ++; id = cnt; len = _len; link = _link; val = _val;
			vis[cnt] = false;
		}
	};

	Node *rt, *la;

	SuffixAutoMaton() {
		cnt = 0;
		rt = new Node(cnt);
		la = rt;
	}

	void extend( const char newchar, cint val = 0 ) {
		Node *new_node = new Node( cnt, la -> len + 1, la, val );
		Node *cur = la; la = new_node;
		while( cur != 0 && cur -> nxt.count(newchar) == 0 ) {
			cur -> nxt[newchar] = new_node;
			cur = cur -> link;
		}

		if( cur == 0 ) {
			new_node -> link = rt;
			return ;
		}

		Node* ori_node = cur -> nxt[newchar];
		if( ori_node -> len == cur -> len + 1 ) {
			new_node -> link = ori_node;
			return ;
		}
		else {
			Node *clone = new Node(cnt);
			*clone = *ori_node;
			clone -> val = 0;
			clone -> id = cnt;
			clone -> len = cur -> len + 1;
			new_node -> link = clone;
			ori_node -> link = clone;
			while( cur != 0 && cur -> nxt[newchar] == ori_node ) {
				cur -> nxt[newchar] = clone;
				cur = cur -> link;
			}
		}
	}

	void build( Graph &g, Node *cur ) {
		if( vis[ cur -> id ] ) 
			return ;
		vis[ cur -> id ] = true;
		f1[ cur -> id ] = cur -> val;
		f2[ cur -> id ] = cur -> len;
		if( cur -> link != 0 ) 
			g.add_edge( cur -> link -> id, cur -> id );
		for( auto &pair: cur -> nxt ) {
			build( g, pair.second );
		}
	}
	void build( Graph &g ) { build( g, rt ); }
};/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "loj.2720.in", "r", stdin );
	freopen( "loj.2720.out", "w", stdout );
#else
	freopen( "name.in", "r", stdin );
	freopen( "name.out", "w", stdout );
#endif
	SuffixAutoMaton sam;
	Graph g;
	{
		static char str[N];
		scanf( "%s", str + 1 );
		cint len = strlen( str + 1 );
		for( int i = 1; i <= len; i ++ ) 
			sam.extend( str[i], i );

		g.init( sam.cnt );
		sam.build(g);
		g.build_sgt( 1, len );
	}
	
	cint q = read<int>();
	for( int _ = 1; _ <= q; _ ++ ) {
		static char str[N];
		SuffixAutoMaton s2;
		scanf( "%s", str + 1 );
		cint len = strlen( str + 1 );
		
		cint l = read<int>();
		cint r = read<int>();

		auto chk_vaild = [r]( SuffixAutoMaton::Node *cur, cint st ) {
			if( cur == 0 ) 
				return false;
			cint pos = sgt[ cur -> id ].max( st, r );
			return pos != 0;
		};

		SuffixAutoMaton::Node *cur = sam.rt;
		int cur_len = 0;
		for( int i = 1; i <= len; i ++ ) {
			while( cur_len != 0 && !chk_vaild( cur -> nxt[ str[i] ], l + cur_len ) ) {
				cur_len --;
				if( cur -> link -> len == cur_len ) 
					cur = cur -> link;
			}
			if( chk_vaild( cur -> nxt[ str[i] ], l + cur_len ) ) {
				cur = cur -> nxt[ str[i] ];
				cur_len += 1;
			}
			s2.extend( str[i], cur_len );
		}

		g.init( s2.cnt );
		s2.build(g);

		printf( "%lld\n", g.dfs( 1, 0 ) );
	}
}
