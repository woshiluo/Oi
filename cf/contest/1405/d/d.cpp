// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/07 21:23:19 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 1e5 + 1e4;

struct edge { int to, next; };

int T;
int n, a, b, da, db;

edge e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next= ehead[cur];
	ehead[cur] = ecnt;
}

int depth[N], fa[N], diam;

inline void init() {
	ecnt = diam = 0;
	memset( ehead, 0, sizeof(ehead) );
	memset( depth, 0, sizeof(depth) );
}

int get_dis( int from, int to ) {
	int res = 0;
	while( from != to ) {
		if( depth[from] < depth[to] ) 
			std::swap( from, to );
		from = fa[from];
		res ++;
	}
	return res;
}

int dfs( int cur, int fat ) {
	depth[cur] = depth[fat] + 1;
	fa[cur] = fat;
	std::priority_queue<int> q;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == fat ) 
			continue;
		q.push( dfs( e[i].to, cur ) );
	}
	if( q.size() == 0 ) {
		return 0;
	}
	else if( q.size() == 1 ) {
		int top1 = q.top() + 1;
		chk_Max( diam, top1 );
		return top1;
	}
	else {
		int top1 = q.top() + 1; q.pop();
		int top2 = q.top() + 1;
		chk_Max( diam, top1 );
		chk_Max( diam, top1 + top2 );
		return top1;
	}
	return 0;
}

void readin() {
	scanf( "%d%d%d%d%d", &n, &a, &b, &da, &db );
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
	}
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		init();
		readin();
		dfs( 1, 0 );
		int dis = get_dis( a, b );
		if( dis <= da ) {
			printf( "Alice\n" );
			continue;
		}
		else if( 2 * da >= diam ) {
			printf( "Alice\n" );
			continue;
		}
		else if( db > 2 * da ) {
			printf( "Bob\n" );
			continue;
		}
		else {
			printf( "Alice\n" );
			continue;
		}
	}
}
