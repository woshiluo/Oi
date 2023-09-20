/*
 * b.cpp
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

const int N = 2e5 + 5;
const int K = 20;
const int INF = 0x3f3f3f3f;

struct Set {/*{{{*/
	int fa[N];

	void init( cint n ) {
		for( int i = 0; i <= n; i ++ )
			fa[i] = i;
	}

	int& get_fa( cint cur ) {
		if( fa[cur] == cur ) 
			return fa[cur];
		int &cfa = get_fa( fa[cur] );
		fa[cur] = cfa;
		return cfa;
	}

	int& operator[] ( cint cur ) { return get_fa(cur); }
} set;/*}}}*/

struct Edge {/*{{{*/
	int to, next;
} e[N];
int ehead[N], ecnt;
void add_edge( cint cur, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/

struct Node {/*{{{*/
	int left, rig, cnt;
	Node *son[2];
	Node( int _left, int _rig ) {
		left = _left; rig = _rig; cnt = 0;
		son[0] = son[1] = 0;
	}

	Node* get_son( cint cur ) {/*{{{*/
		cint mid = ( left + rig ) >> 1;
		if( son[cur] == 0 ) {
			if( cur == 0 )
				son[cur] = new Node( left, mid );
			if( cur == 1 )
				son[cur] = new Node( mid + 1, rig );
		}

		return son[cur];
	}/*}}}*/

	Node* operator[] ( cint cur ) { return this -> get_son(cur); }
	void push_up() { cnt = ( son[0]? son[0] -> cnt: 0 ) + ( son[1]? son[1] -> cnt: 0 ); }

	void add( int pos, int val ) {/*{{{*/
		if( left == rig ) {
			cnt += val;
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		if( pos <= mid ) 
			(*this)[0] -> add( pos, val );
		else
			(*this)[1] -> add( pos, val );

		this -> push_up();
	}/*}}}*/

	int query( cint from, cint to ) const {/*{{{*/
		if( from <= left && rig <= to ) 
			return this -> cnt;
		cint mid = ( left + rig ) >> 1;
		int res = 0;
		if( from <= mid && son[0] ) 
			res += son[0] -> query( from, to );
		if( to > mid && son[1] ) 
			res += son[1] -> query( from, to );
		return res;
	}/*}}}*/
} *rt[N];/*}}}*/

Node* merge( Node *lr, Node * rr ) {/*{{{*/
	if( lr && !rr ) 
		return lr;
	if( rr && !lr ) 
		return rr;
	if( !lr && !rr ) 
		return 0;

	Node *cur = new Node( lr -> left, lr -> rig );
	cur -> cnt = lr -> cnt + rr -> cnt;

	cur -> son[0] = merge( lr -> son[0], rr -> son[0] );
	cur -> son[1] = merge( lr -> son[1], rr -> son[1] );

	return cur;
}/*}}}*/

int idx;
int dfn[N], size[N], val[N];
int fa[N][K];
void dfs( cint cur ) {/*{{{*/
	idx ++;
	dfn[cur] = idx;
	size[cur] = 1;
	for( int k = 1; k < K; k ++ ) 
		fa[cur][k] = fa[ fa[cur][ k - 1 ] ][ k - 1 ];
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		fa[to][0] = cur;
		dfs(to);
		size[cur] += size[to];
	}
}/*}}}*/

void init( cint cur ) {/*{{{*/
	Node *rt0 = 0, *rt1 = 0;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		init(to);
		if( !rt0 ) 
			rt0 = rt[ dfn[to] ];
		else
			rt1 = rt[ dfn[to] ];
	}

	if( !rt0 ) 
		return ;

	rt[ dfn[cur] ] = merge( rt0, rt1 );
}/*}}}*/

bool check( int from, int to, cint mid ) {/*{{{*/
	for( int k = K - 1; k >= 0; k -- ) 
		if( fa[from][k] && val[ fa[from][k] ] <= mid ) 
			from = fa[from][k];
	for( int k = K - 1; k >= 0; k -- ) 
		if( fa[to][k] && val[ fa[to][k] ] <= mid ) 
			to = fa[to][k];

	if( rt[ dfn[from] ] -> query( dfn[to], dfn[to] + size[to] - 1 ) ) 
		return true;
	if( rt[ dfn[to] ] -> query( dfn[from], dfn[from] + size[from] - 1 ) ) 
		return true;

	return false;
}/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	cint on = read<int>();
	cint m = read<int>();
	cint q = read<int>();

	int n = on;
	{/*{{{*/
		set.init( on << 1 );
		for( int i = 1; i <= n; i ++ )
			val[i] = INF;

		struct OEdge { int u, v, w; };
		std::vector<OEdge> edges;
		for( int i = 1; i <= m; i ++ ) {
			cint u = read<int>();
			cint v = read<int>();
			cint w = read<int>();
			edges.push_back( (OEdge) { u, v, w } );
		}
		std::sort( edges.begin(), edges.end(), []( const OEdge &_a, const OEdge &_b ) { return _a.w < _b.w; });
		for( auto &edge: edges ) {
			cint u = set[ edge.u ];
			cint v = set[ edge.v ];
			if( u == v ) 
				continue;
			n ++; val[n] = edge.w;
			add_edge( n, u );
			add_edge( n, v );
			set[u] = n; set[v] = n;
		}

		for( int i = n; i >= 1; i -- ) 
			if( !dfn[i] )
				dfs(i);

		for( int i = 1; i <= on; i ++ ) 
			rt[ dfn[i] ] = new Node( 1, n );
		for( auto &edge: edges ) {
			cint u = edge.u;
			cint v = edge.v;
			rt[ dfn[u] ] -> add( dfn[v], 1 );
		}

		for( int i = n; i >= 1; i -- ) 
			if( !rt[ dfn[i] ] )
				init(i);
	}/*}}}*/

	for( int i = 1; i <= q; i ++ ) {
		cint x = read<int>();
		cint y = read<int>();

 		int left = 0, rig = 1e9, res = INF;
		while( left <= rig ) {
			cint mid = ( left + rig ) >> 1;
			if( check( x, y, mid ) ) {
				res = mid;
				rig = mid - 1;
			}
			else
				left = mid + 1;
		}

		printf( "%d\n", res == INF? -1: res );
	}
}
