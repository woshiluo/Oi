/*
 * str.cpp
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

const int N = 2e5 + 1e4;

int nval[N], pos[N];

struct SegmentTree {/*{{{*/
	int n;
	struct Node {/*{{{*/
		ll sum, val, lazy;

		void operator+= ( const ll p ) {
			lazy += p;
			sum += val * p;
		}
	} tree[ N << 2 ];/*}}}*/

	void push_up( cint cur ) { tree[cur].sum = tree[ cur << 1 ].sum + tree[ cur << 1 | 1 ].sum; }
	void push_down( cint cur ) {/*{{{*/
		if( tree[cur].lazy ) {
			ll &l = tree[cur].lazy;
			tree[ cur << 1 ] += l;
			tree[ cur << 1 | 1 ] += l;
			l = 0;
		}
	}/*}}}*/

	void query_add( cint from, cint to, cint val, cint cur, cint left, cint rig ) {/*{{{*/
		if( from <= left && rig <= to ) {
			tree[cur] += val;
			return ;
		}

		push_down(cur);
		cint mid = ( left + rig ) >> 1;

		if( from <= mid )
			query_add( from, to, val, cur << 1, left, mid );
		if( to > mid )
			query_add( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}/*}}}*/
	void query_add( cint from, cint to, cint val ) { query_add( from, to, val, 1, 1, n ); }

	ll query_sum( cint from, cint to, cint cur, cint left, cint rig ) {/*{{{*/
		if( from <= left && rig <= to ) {
			return tree[cur].sum;
		}

		push_down(cur);
		ll res = 0;
		cint mid = ( left + rig ) >> 1;

		if( from <= mid ) 
			res += query_sum( from, to, cur << 1, left, mid );
		if( to > mid ) 
			res += query_sum( from, to, cur << 1, left, mid );

		return res;
	}/*}}}*/
	void query_sum( cint from, cint to ) { query_sum( from, to, 1, 1, n ); }

	void build( cint cur, cint left, cint rig ) {/*{{{*/
		tree[cur] = (Node) { 0, 0, 0 };
		if( left == rig ) {
			tree[cur].val = nval[left];
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );

		tree[cur].val = tree[ cur << 1 ].val + tree[ cur << 1 | 1 ].val;
	}/*}}}*/
	void init( cint _n ) { n = _n; build( 1, 1, n ); }
} sgt;/*}}}*/

struct Edge {/*{{{*/
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( cint from, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}/*}}}*/

int fa[N], dep[N], size[N], mson[N];
void dfs1( cint cur, cint la ) {/*{{{*/
	fa[cur] = la; dep[cur] = dep[la] + 1;
	size[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		if( to == la ) 
			continue;

		dfs1( to, cur );
		size[cur] += size[to];
		if( size[to] > size[ mson[cur] ] ) 
			mson[cur] = to;
	}
}/*}}}*/

int idx;
int dfn[N], top[N];
void dfs2( cint cur, cint la ) {/*{{{*/
	idx ++; dfn[cur] = idx;
	if( top[cur] == 0 )
		top[cur] = cur;
	if( mson[cur] == 0 ) 
		return ;

	top[ mson[cur] ] = top[cur];
	dfs2( mson[cur], cur );

	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la || e[i].to == mson[cur] )
			continue;
		dfs2( e[i].to, la );
	}
}/*}}}*/

struct SAM {/*{{{*/
	const static int K = 30;
	int cnt = 1, last = 1;
	struct Node {/*{{{*/
		int id, len, link;
		int nxt[K];
		Node() {
			id = len = link = 0;
			memset( nxt, 0, sizeof(nxt) );
		}
	} nodes[ N << 2 ];
	SAM() { nodes[cnt].id = 1; }/*}}}*/

	int get_new() {/*{{{*/
		cnt ++;
		nodes[cnt].id = cnt;
		return cnt;
	}
	void copy_to( cint from, cint to ) {
		nodes[from].link = nodes[to].link;
		memcpy( nodes[to].nxt, nodes[from].nxt, sizeof(nodes[from].nxt) );
	}/*}}}*/

	int extend( int new_char ) {
		cint cur = get_new();
		nodes[cur].len = nodes[last].len + 1;
		int p = last;
		while( p != 0 && nodes[p].nxt[new_char] == 0 ) {
			nodes[p].nxt[new_char] = cur;
			p = nodes[p].link;
		}

		if( p == 0 ) 
			nodes[cur].link = 1;
		else {
			cint q = nodes[cur].nxt[new_char];
			if( nodes[p].len + 1 == nodes[q].len ) 
				nodes[cur].link = q;
			else {
				cint clone = get_new();
				copy_to( q, clone );
				{
					int tmp = p;
					while( tmp != 0 && nodes[tmp].nxt[new_char] == q ) {
						nodes[tmp].nxt[new_char] = clone;
						tmp = nodes[tmp].link;
					}
				}
				nodes[q].link = nodes[cur].link = clone;
			}
		}

		last = cur;
		return cur;
	}
};/*}}}*/

int main() {
	freopen( "str.in", "r", stdin );
	freopen( "str.out", "w", stdout );

	static char str[N];
	scanf( "%s", str + 1 );

	cint len = strlen( str + 1 );
}
