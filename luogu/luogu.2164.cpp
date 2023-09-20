#include <cstdio>

#include <queue>

const int N = 310;
const int M = N * N * 2;

// Edge Start 
struct edge { int to, next; };

int ehead[N], ecnt;
edge e[ N << 1 ];
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}
// Edge End

// BFS Start
int dis[N][N];
void dfs( int st, int dis[] ) {
	std::queue<int> q; bool vis[N];

	memset( dis, INF, sizeof(dis) );
	memset( vis, 0, sizeof(vis) );

	q.push_back(st); dis[st] = 0;
	while( !q.empty() ) {
		int cur = q.front(); q.pop();
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( dis[ e[i].to ] >= dis[ e[i].cur ] + 1 ) {
				dis[ e[i].to ] = dis[ e[i].cur ] + 1;
				if( vis[ e[i].to ] == false ) {
					vis[ e[i].to ] = true;
					q.push( e[i].to );
				}
			}
		}
	}
}
// BFS End

double val[M];

void calc( int from, int to, int val ) {
	int cnt[N]; bool alloewd[M];
	memset( cnt, 0, sizeof(cnt) );
	memset( alloewd, 0, sizeof(alloewd) );

	for( int cur = 1; cur <= n; cur ++ ) {
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( dis[from][cur] + dis[to][ e[i].to ] + 1 == dis[from][to] ) {
				alloewd[i] = true;
				in_degree[cur] ++;
			}
		}
	}

	{
		std::queue<int> q;

		cnt[from] = 1; q.push(from);
		while( !q.empty() ) {
			int cur = q.front(); q.pop();
			for( int i = ehead[cur]; i; i = e[i].next ) {
				if( alloewd[i] )
					cnt[ e[i].to ] += cnt[cur];
			}
		}
	}

	{
		std::queue<int> q;
		q.push(to);
		while( !q.empty() ) {
			int cur = q.front(); q.pop();
			for( int i = ehead[cur]; i; i = e[i].next ) {
				if( alloewd[i] ) {
					in_degree[ e[i].to ] --;
					if( in_degree[ e[i].to ] == 0 ) {
						q.push( e[i].to );
					}
				}
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.2164.in", "r", stdin );
	freopen( "luogu.2164.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= m; i ++ ) {
		int x, y;
		scanf( "%d%d", &x, &y );
		add_edge( x, y );
		add_edge( y, x );
	}

	for( int i = 1; i <= n; i ++ ) {
		bfs( i, dis[i] );
	}

	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			int tmp;
			scanf( "%d", &tmp );
			calc( i, j, tmp );
		}
	}
}
