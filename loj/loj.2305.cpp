/*
 * loj.2305.cpp
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

#include <stack>
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

const int N = 5e5 + 1e4;

struct Op { int u, x, v, y; };

int n;
int a[N];

std::vector<int> xlist;
std::vector<Op> ops;

inline int full_pow( cint cur ) { return 1 << cur; }
inline bool chk_pos( cint cur, cint p ) { return cur & full_pow(p); }

struct Edge {
	int to, next;
} e[ N << 3 ];
int ehead[N], ecnt;
inline void add_edge( cint cur, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int tidx = 0, colcnt = 0;
int low[N], dfn[N], col[N];
bool vis[N], block[N], block_col[N];
std::stack<int> stack;
void trojan( int cur ) {
	tidx ++;
	vis[cur] = true;
	stack.push(cur);
	dfn[cur] = low[cur] = tidx;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		if( !dfn[to] ) {
			trojan(to);
			chk_Min( low[cur], low[to] );
		}
		else if( vis[to] ) 
			chk_Min( low[cur], dfn[to] );
	}
	if( dfn[cur] == low[cur] ) { 
		colcnt ++;
		while( dfn[ stack.top() ] != low[ stack.top() ] ) {
			cint node = stack.top(); stack.pop();
			col[node] = colcnt;
			vis[node] = false;
		}
		{
			cint node = stack.top(); stack.pop();
			col[node] = colcnt;
			vis[node] = false;
		}
	}
}

int hash( cint cur, cint p ) { return p * n + cur; }
bool chk( cint cur, cint val ) { return a[cur] == val; }
void try_solve() {
	tidx = 0; colcnt = 0; ecnt = 0;
	memset( ehead, 0, sizeof(ehead) );
	memset( low, 0, sizeof(low) );
	memset( dfn, 0, sizeof(dfn) );
	memset( vis, 0, sizeof(vis) );
	std::vector<std::vector<int>> id( n + 1 ), mp( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j < 3; j ++ ) {
			if( chk( i, j ) ) 
				continue;
			id[i].push_back( hash( i, j ) );
			mp[i].push_back(j);
		}
	}
	for( auto &op: ops ) {
		if( chk( op.u, op.x ) ) 
			continue;
		cint fid = ( mp[ op.u ][1] == op.x );

		if( chk( op.v, op.y ) ) {
			block[ id[ op.u ][fid] ] = true;
			add_edge( id[ op.u ][fid], id[ op.u ][ fid ^ 1 ] );
			continue;
		}
		cint tid = ( mp[ op.v ][1] == op.y );
		add_edge( id[ op.u ][fid], id[ op.v ][tid] );
		add_edge( id[ op.v ][ tid ^ 1 ], id[op.u][ fid ^ 1 ]  );
	}
	
	for( int i = 1; i <= ( n * 3 ); i ++ ) {
		if( !dfn[i] ) 
			trojan(i);
	}

	for( int i = 1; i <= n; i ++ ) {
		cint d1 = id[i][0];
		cint d2 = id[i][1];
		if( col[d1] == col[d2] ) 
			return ;
	}

	// Re-use vis and scc
	for( int i = 1; i <= n; i ++ ) {
		cint d1 = id[i][0];
		cint d2 = id[i][1];
		if( vis[ col[d1] ] ) {
			printf( "%c", 'A' + mp[i][0] );
		}
		else if( vis[ col[d2] ] ) {
			printf( "%c", 'A' + mp[i][1] );
		}
		else if( col[d1] < col[d2] ) {
			vis[ col[d1] ] = true;
			printf( "%c", 'A' + mp[i][0] );
		}
		else {
			vis[ col[d2] ] = true;
			printf( "%c", 'A' + mp[i][1] );
		}
	}
	std::exit(0);
}

int get_id() {
	static char op[3];
	scanf( "%s", op );
	return op[0] - 'A';
}
int main() {
#ifdef woshiluo
	freopen( "loj.2305.in", "r", stdin );
	freopen( "loj.2305.out", "w", stdout );
#endif
	n = read<int>();
	cint d = read<int>();
	static char str[N];
	scanf( "%s", str + 1 );

	for( int i = 1; i <= n; i ++ ) {
		if( str[i] == 'x' ) {
			a[i] = 3;
			xlist.push_back(i);
		}
		else
			a[i] = ( str[i] - 'a' );
	}

	cint m = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		cint u = read<int>();
		cint hu = get_id();
		cint v = read<int>();
		cint hv = get_id();
		if( u == v && hu == hv ) 
			continue;
		ops.push_back( (Op){ u, hu, v, hv } );
	}

	for( int i = 0; i < full_pow(d); i ++ ) {
		for( int j = 0; j < d; j ++ ) {
			a[ xlist[j] ] = chk_pos( i, j );
		}
		try_solve();
	}
	printf( "-1\n" );
}
