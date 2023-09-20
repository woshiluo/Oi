/*
 * e.cpp 2023-08-30
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

#include <set>
#include <queue>
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

const int N = 2e5 + 1e4;
const int M = 2e5 + 1e4;

struct Edge {
	int to, next, val;
} e[ N + M ];
int ehead[N], ecnt;
void add_edge( cint from, cint to, cint val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

void init( cint n ) {
	ecnt = 0;
	memset( ehead, 0, sizeof(int) * ( n + 1 ) );
}


void work() {
	cint n = read<int>();
	cint m = read<int>();
	cint k = read<int>();

	init(n);

	std::vector<int> h( n + 1 ), indegree( n + 1 ), outdegree( n + 1 );
	std::vector<ll> f( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		h[i] = read<int>();
	}

	for( int i = 1; i <= m; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();
		indegree[u] ++;
		outdegree[v] ++;
		if( h[u] <= h[v] )
			add_edge( v, u, h[v] - h[u] );
		else
			add_edge( v, u, k - h[u] + h[v] );
	}

	std::queue<int> q;
	for( int i = 1; i <= n; i ++ ) {
		if( indegree[i] == 0 ) {
			q.push(i);
		}
	}

	while( !q.empty() ) {
		cint cur = q.front(); q.pop();

		for( int i = ehead[cur]; i; i = e[i].next ) {
			cint to = e[i].to;
			indegree[to] --;
			chk_Max( f[to], f[cur] + e[i].val );
			if( indegree[to] == 0 ) 
				q.push(to);
		}
	}

	ll cur_r = 0;
	struct Seg { ll l, r; };
	std::vector<Seg> segs;
	std::multiset<ll> set;
	for( int i = 1; i <= n; i ++ ) {
		if( outdegree[i] == 0 ) {
			segs.push_back( (Seg) { (ll)h[i], (ll)h[i] + f[i] } );
			set.insert(h[i]);
			chk_Max( cur_r, segs.back().r );
		}
	}

	std::sort( segs.begin(), segs.end(), []( const Seg &_a, const Seg &_b ) {
		if( _a.r == _b.r ) 
			return _a.l > _b.l;
		else
			return _a.r < _b.r;
	});

	ll ans = cur_r;
	for( auto &seg: segs ) {
		chk_Min( ans, cur_r - *set.begin() );
		chk_Max( cur_r, seg.r + k );
		set.erase( set.find( seg.l ) );
		set.insert( seg.l + k );
	}

	printf( "%lld\n", ans );
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		work();
	}
}
