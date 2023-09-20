/*
 * buffoonery.cpp
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

const int N = 1e5 + 1e4;

struct Edge { int to, next; } e[ N << 1 ];/*{{{*/
int ehead[N], ecnt;
void add_edge( cint cur, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/

int weight[N], value[N];

int dfn[N], mp[N], idx;
int size[N];
void dfs( cint cur ) {
	idx ++; dfn[cur] = idx; mp[idx] = cur;
	size[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		dfs(to);
		size[cur] += size[to];
	}
}

struct Query { int id, left, rig; };
struct Bag {
	unsigned m;
	std::vector<ull> f;

	void init( unsigned _m ) { m = _m; f.resize( m + 1 ); }

	void add( const ull w, const ull v ) {
		for( unsigned i = m; i >= w; i -- ) 
			chk_Max( f[i], f[ i - w ] + v );
	}

	ull get_ans( cint k ) {
		ull res = 0;
		for( ull i = 0; i <= m; i ++ ) {
			res ^= f[i] * pow( i + 1, k );
		}
		return res;
	}
};

ull res[N][2];

void work( cint left, cint rig, std::vector<Query> queries, Bag f ) {
	if( queries.size() == 0 )
		return ;
	if( left == rig ) {
		for( auto &q: queries ) {
			res[ q.id ][0] = f.get_ans(1);
			res[ q.id ][1] = f.get_ans(3);
		}
		return ;
	}
	std::vector<Query> lq, rq, cq;
	cint mid = ( left + rig ) >> 1;
	
	for( auto &q: queries ) {
		if( q.rig <= mid )
			lq.push_back(q);
		else if( q.left > mid )
			rq.push_back(q);
		else 
			cq.push_back(q);
	}

	std::sort( cq.begin(), cq.end(), []( const Query &_a, const Query &_b ) { 
		if( _a.left == _b.left ) 
			return _a.rig < _b.rig;
		return _a.left < _b.left;
	});

	Bag lf = f, rf = f;
	for( int i = left; i <= mid; i ++ ) 
		lf.add( weight[ mp[i] ], value[ mp[i] ] );
	for( int i = mid + 1; i <= rig; i ++ ) 
		rf.add( weight[ mp[i] ], value[ mp[i] ] );

	int l = left, r = rig;
	for( auto &q: cq ) {
		while( l < q.left ) {
			f.add( weight[ mp[l] ], value[ mp[l] ] );
			l ++;
		}
		while( r > q.rig ) {
			f.add( weight[ mp[r] ], value[ mp[r] ] );
			r --;
		}
		res[ q.id ][0] = f.get_ans(1);
		res[ q.id ][1] = f.get_ans(3);
	}

	work( left, mid, lq, rf );
	work( mid + 1, rig, rq, lf );
}

int main() {
#ifdef woshiluo
	freopen( "buffoonery.in", "r", stdin );
	freopen( "buffoonery.out", "w" ,stdout );
#endif

	cint n = read<int>();
	cint m = read<int>();
	{ int _ = read<int>(); std::swap( _, _ ); } // F**k -Wall
	
	for( int i = 1; i <= n; i ++ ) {
		weight[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		value[i] = read<int>();
	}

	for( int i = 2; i <= n; i ++ ) {
		cint u = read<int>();
		add_edge( u, i );
	}

	dfs(1);

	std::vector<Query> queries;
	for( int i = 2; i <= n; i ++ ) {
		queries.push_back( (Query) { i, dfn[i], dfn[i] + size[i] - 1 } );
	}

	Bag f;
	f.init(m);
	work( 1, n, queries, f );

	for( int i = 2; i <= n; i ++ ) 
		printf( "%llu %llu\n", res[i][0], res[i][1] );
}
