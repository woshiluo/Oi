/*
 * trip.cpp
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

typedef long long ll;
typedef unsigned long long ull;
typedef const int cint;
typedef const ll cll;

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
const int M = 2e5 + 1e4;
const int K = 21;
const int INF = 0x3f3f3f3f;


struct Edge {
	int to, next, val;
} e[ M << 1 ];
int ehead[N], ecnt;
void add_edge( cint cur, cint to, cint val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

ll dis[K][N];

void dij( cint st, ll d[] ) {/*{{{*/
	struct Dis { /*{{{*/
		ll dis; int cur; 

		bool operator< ( const Dis &_b ) const { return dis > _b.dis; }
	};/*}}}*/

	static std::priority_queue<Dis> q;
	static bool vis[N];
	
	memset( vis, 0, sizeof(vis) );
	memset( d, INF, sizeof( dis[0] ) );

	d[st] = 0; q.push( { d[st], st } );

	while( !q.empty() ) {
		cint cur = q.top().cur; q.pop();

		if( vis[cur] ) 
			continue;
		vis[cur] = true;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			cint to = e[i].to, val = e[i].val;
			if( d[cur] + val < d[to] ) {
				d[to] = d[cur] + val;
				q.push( { d[to], to } );
			}
		}
	}
}/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "trip.in", "r", stdin );
	freopen( "trip.out", "w", stdout );
#endif
	cint n = read<int>();/*{{{*/
	cint m = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();
		cint w = read<int>();

		add_edge( u, v, w );
		add_edge( v, u, w );
	}

	cint ptot = read<int>();
	std::vector<int> p; p.push_back(1);
	for( int i = 1; i <= ptot; i ++ ) {
		p.push_back( read<int>() );
	}
	std::sort( p.begin(), p.end() ); p.erase( std::unique( p.begin(), p.end() ), p.end() );
	cint k = p.size();/*}}}*/

	for( int i = 0; i < k; i ++ ) {
		dij( p[i], dis[i] );
	}

	ll ans = ( 1LL << 60 );

	for( int i = 1; i <= n; i ++ ) {
		ll res = 0;
		for( int j = 0; j < k; j ++ ) {
			chk_Max( res, dis[j][i] );
		}
		chk_Min( ans, res << 1 );
	}

	for( int from = 1; from <= n; from ++ ) {
		for( int i = ehead[from]; i; i = e[i].next ) {
			cint to = e[i].to;
			cll val = e[i].val;
			if( to < from ) 
				continue;

			struct Dis { /*{{{*/
				ll dis; int cur; 

				bool operator< ( const Dis &_b ) const { return dis < _b.dis; }
			};/*}}}*/

			std::priority_queue<Dis> q[2];
			for( int j = 0; j < k; j ++ ) 
				q[0].push( { dis[j][from], j } );

			for( int j = 0; j < k; j ++ ) {
				{/*{{{*/
					cint top = q[0].top().cur; q[0].pop();
					q[1].push( { dis[top][to], top } );

					if( q[0].empty() || q[1].empty() ) 
						continue;
				}/*}}}*/

				ll fir = q[0].top().dis, sec = q[1].top().dis;
				if( fir > sec ) 
					std::swap( fir, sec );

				if( sec - fir >= val ) 
					continue;

				chk_Min( ans, sec * 2LL + ( val - ( sec - fir ) ) );
			}
		}
	}

	printf( "%lld\n", ans );
}
