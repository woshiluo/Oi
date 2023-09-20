/*
 * luogu.6329.cpp
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

#include <queue>
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

const int N = 1e5 + 1e4;

struct Edge {/*{{{*/
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int from, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}/*}}}*/

struct SegmentTree {/*{{{*/
	struct Node {/*{{{*/
		cint left, rig, mid;
		int sum;
		Node *son[2];
		Node( cint _left, cint _rig, cint _sum = 0 ): left(_left), rig(_rig), mid( ( _left + _rig ) >> 1 ), sum(_sum) { son[0] = son[1] = 0; }

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
		bool contained_by( cint from, cint to ) { return from <= left && rig <= to; }
		bool contained_by( cint pos ) { return contained_by( pos, pos ); }
	};/*}}}*/
	Node *rt;

	SegmentTree( cint n = N ) :rt( new Node( 0, n ) ) {}

	void add( cint pos, cint val, Node *cur ) {
		if( cur -> contained_by(pos) ){
			cur -> sum += val;
			return ;
		} 

		cint mid = cur -> mid;
		if( pos <= mid ) 
			add( pos, val, cur -> get_son(0) );
		if( pos > mid ) 
			add( pos, val, cur -> get_son(1) );

		cur -> push_up();
	}
	void add( cint pos, cint val ) { return add( pos, val, rt ); }

	int sum( cint from, cint to, Node *cur ) {
		if( cur -> contained_by( from, to ) ) {
			return cur -> sum;
		}
		
		int res = 0;
		cint mid = cur -> mid;
		if( from <= mid ) 
			res += sum( from, to, cur -> get_son(0) );
		if( to > mid ) 
			res += sum( from, to, cur -> get_son(1) );

		return res;
	}
	int sum( cint from, cint to ) { 
		if( to < from ) 
			return 0;
		return sum( from, to, rt );
	}
} sgts[N][2];/*}}}*/

int val[N];

std::vector<int> flist[N], fdis[N];

int size[N]; bool block[N]; 

void build_init( cint cur, cint la, cint fa, cint dis ) {
	size[cur] = 1; 

	sgts[fa][0].add( dis, val[cur] );
	if( flist[cur].size() )
		sgts[fa][1].add( fdis[cur].back(), val[cur] );
	flist[cur].push_back(fa);
	fdis[cur].push_back(dis);

	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		if( to == la || block[to] ) 
			continue;

		build_init( to, cur, fa, dis + 1 );
		size[cur] += size[to];
	}
}

void get_root( cint cur, cint la, cint tot, int &pos, int &res ) {
	int max = tot - size[cur];
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		if( to == la || block[to] ) 
			continue;

		get_root( to, cur, tot, pos, res );
		chk_Max( max, size[to] );
	}
	if( max < res ) {
		res = max;
		pos = cur;
	}
}

void build( cint cur, cint la ) {
	block[cur] = true;

	build_init( cur, la, cur, 0 );

	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		if( to == la || block[to] ) 
			continue;

		int rt = 0, res = size[to] + 1;
		get_root( to, cur, size[to], rt, res );
		build( rt, la );
	}
}

struct ReadIn {/*{{{*/
	int res = 0;
	ReadIn(): res(0) {};

	int get() {
		int x = read<int>();
		x ^= res;
		return x;
	}

	void update( cint _res ) {
		res = _res;
		printf( "%d\n", res );
	}
} readin;/*}}}*/

void update( cint pos, cint nval ) {
	cint tot = flist[pos].size();
	for( int i = 0; i < tot; i ++ ) {
		sgts[ flist[pos][i] ][0].add( fdis[pos][i], nval - val[pos] );
		if( i - 1 >= 0 )
			sgts[ flist[pos][i] ][1].add( fdis[pos][ i - 1 ], nval - val[pos] );
	}
	val[pos] = nval;
}

int query( cint from, cint k ) {
	cint tot = flist[from].size();
	int res = 0;
	for( int i = tot - 1; i >= 0; i -- ) {
		cint cur_fa = flist[from][i];
		res += sgts[cur_fa][0].sum( 0, k - fdis[from][i] );
		if( i - 1 >= 0 )
			res -= sgts[cur_fa][1].sum( 0, k - fdis[from][ i - 1 ] );
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.6329.in", "r", stdin );
	freopen( "luogu.6329.out", "w", stdout );
#endif
	const int n = read<int>(); 
	int q = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		val[i] = read<int>();
	}
	for( int i = 1; i < n; i ++ ) {
		const int u = read<int>();
		const int v = read<int>();
		add_edge( u, v );
		add_edge( v, u );
	}

	build( 1, 0 );

	while( q -- ) {
		int op = read<int>();
		int x = readin.get();
		int y = readin.get();
		if( op == 0 ) 
			readin.update( query( x, y ) );
		else 
			update( x, y );
	}
}
