#include <cstdio>
#include <cstring>

#include <queue>

const int N = 2e6 + 1e5;

int n, m, q;
int fa[N];

int get_fa( int cur ) {
	if( fa[cur] == cur ) 
		return cur;
	return fa[cur] = get_fa( fa[cur] );
}

struct edge { int to, next, val; };

int ehead[N], ecnt;
edge e[ N << 1 ];
inline void add_edge( int cur, int to, int val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int query( int from, int to ) {
	int dis[N];
	std::queue<int> q;
	memset( dis, -1, sizeof(dis) );
	dis[from] = 0;
	q.push(from);
	while( !q.empty() ) {
		int cur = q.front(); q.pop();
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( dis[ e[i].to ] != -1 ) 
				continue;
			dis[ e[i].to ] = std::max( dis[cur], e[i].val );
			q.push( e[i].to );
		}
	}
	return dis[to]; 
}

int main() {
#ifdef woshiluo
	freopen( "noi.2170.in", "r", stdin );
	freopen( "noi.2170.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &q );
	for( int i = 1; i <= n + n; i ++ ) {
		fa[i] = i;
	}
//	for( int i = 1; i <= n; i ++ ) {
//		fa[i] = i + n;
//		add_edge( i, i + n, 0 );
//		add_edge( i + n, i, 0 );
//	}
	for( int i = 1; i <= m; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		int to_u = n + u, to_v = n + v;
		int fa_u = get_fa(u), fa_v = get_fa(v),
			fa_tou = get_fa(to_u), fa_tov = get_fa(to_v);
		if( fa_u != fa_tov || fa_tou != fa_tov ) {
			fa[fa_u] = fa[fa_tov];
			fa[fa_tou] = fa[fa_tov];
			add_edge( u, to_v, i );
			add_edge( to_v, u, i );
			add_edge( to_u, to_v, i );
			add_edge( to_v, to_u, i );
		}
	}

	while( q -- ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		if( u == v ) {
			printf( "0\n" );
			continue;
		}
		int to_v = n + v, to_u = n + u;
		if( get_fa(to_v) != get_fa(u) || get_fa(to_u) != get_fa(v) ) {
			printf( "-1\n" );
			continue;
		}
		printf( "%d\n", std::min( query( to_u, to_v ), std::max( query( u, to_v ), query( v, to_u ) ) ) );
	}
}
