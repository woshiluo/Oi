#include <cstdio>

int n, m;

struct edge {
	int to, next, flow;
} e[ N << 1 ];
int ehead[N], ecnt = 1;

inline void add_edge( int now, int to, int flow ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].flow = floe;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}

namespace Dinic {
	int S, T;
	int q[N], head, tail;
	bool bfs( int S, int T ) {
		memset( dep, 0, sizeof( dep ) );
		head = tail = 0;
		q[head] = 0; dep[S] = 1;
		while( head <= tail ) {
			int top = q[head];
			for( int i = ehead[top]; i; i = e[i].next ) {
				if( e[i].flow != 0 && dep[top] == 0 ) {
					dep[ e[i].to ] = dep[top] + 1;
					q[ ++ tail ] = e[i].to;
				}
			}
			head ++;
		}
		return dep[T] != 0;
	}
	void init_cache_head() {
		for( int i = 1; i <= n; i ++ ) 
			cache_head[i] = head[i];
	}
	int dfs( int now, int dist ) {
		if( now == T ) 
			return dist;
		int res = 0;
		for( int &i = cache_head[now]; i; i = e[i].next ) {
			if( e[i].flow != 0 && dep[ e[i].to ] == dep[now] + 1 ) {
				int flow = Min( dist, e[i].flow );
				e[ i ^ 1 ].flow -= flow;
				e[i].flow += flow;
				dist -= flow;
				res += dfs( e[i].to, flow );
			}
			if( dist == 0 ) 
				break;
		}
		return res;
	}
	int dinic() {
		int res = 0;
		while( bfs( S, T ) ) {
			init_cache_head();
			while( int d = dfs( S ) ) 
				res += d;
		}
		return res;
	}
}

int main() {
	scanf( "%d%d%d%d", &n, &m, &Dinic::S, &Dinic::T );
	for( int i = 1, u, v, w; i <= n; i ++ ) {
		scanf( "%d%d%d", &u, &v, &w );
		add_edge( u, v, w );
		add_edge
	}
}
