#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <vector>

const int N = 1100;
const int M = 2100;

int n, m;

inline void no_answer() {
	printf( "-1\n" );
	exit(0);
}

struct Graph {
	struct edge { int from, to, next, val; };

	int ecnt;
	int ehead[N], dis[N];
	edge e[M];

	Graph() {
		ecnt = 0;
		memset( dis, -1, sizeof(dis) );
		memset( ehead, 0, sizeof(ehead) );
	}

	inline void add_edge( int cur, int to, int val = 0 ) {
		ecnt ++;
		( this -> e[ecnt] ).from = cur;
		( this -> e[ecnt] ).to = to;
		( this -> e[ecnt] ).val = val;
		( this -> e[ecnt] ).next = ehead[cur];
		ehead[cur] = ecnt;
	}
	void get_dis( int st ) {
		std::queue<int> q;
		q.push(st);
		dis[st] = 0;
		while( !q.empty() ) {
			int cur = q.front(); q.pop();
			for( int i = ehead[cur]; i; i = e[i].next ) {
				if( dis[ e[i].to ] == -1 ) {
					dis[ e[i].to ] = dis[cur] + 1;
					q.push( e[i].to );
				}
			}
		}
	}
	void spfa( int st ) {
		int cnt[N];
		bool vis[N];
		memset( cnt, 0, sizeof(cnt) );
		memset( vis, 0, sizeof(vis) );
		std::queue<int> q;
		q.push(st);
		dis[st] = 0; vis[st] = true; cnt[st] = 1;
		while( !q.empty() ) {
			int cur = q.front(); q.pop();
			for( int i = ehead[cur]; i; i = e[i].next ) {
				if( dis[ e[i].to ] < dis[cur] + e[i].val ) {
					dis[ e[i].to ] = dis[cur] + e[i].val;
					if( vis[ e[i].to ] == false ) {
						cnt[ e[i].to ] ++;
						if( cnt[ e[i].to ] >= n ) 
							no_answer();
						q.push( e[i].to );
					}
				}
			}
			vis[cur] = false;
		}
	}

	inline int start( int id ) { return ehead[id]; }
	inline int get_to( int id ) { return e[id].to; }
	inline int get_from( int id ) { return e[id].from; }
	inline int next( int id ) { return e[id].next; }
} pre[2], graph;

inline bool is_end( int id ) { return id == 0; }

int main() {
#ifdef woshiluo
	freopen( "luogu.5590.in", "r", stdin );
	freopen( "luogu.5590.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= m; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		pre[0].add_edge( u, v );
		pre[1].add_edge( v, u );
	}

	pre[0].get_dis(1); pre[1].get_dis(n);
	if( pre[0].dis[n] == -1 ) {
		no_answer();
	}
	bool vis[N];
	memset( vis, 0, sizeof(vis) );
	for( int i = 1; i <= n; i ++ ) {
		if( pre[0].dis[i] != -1 && pre[1].dis[i] != -1 ) {
			vis[i] = true;
		}
	}
	for( int o = 1; o <= n; o ++ ) {
		if( vis[o] == false ) 
			continue;
		for( int i = pre[0].start(o); !is_end(i); i = pre[0].next(i) ) {
			int to = pre[0].get_to(i);
			if( vis[to] ) {
				graph.add_edge( o, to, 1 );
				graph.add_edge( to, o, -9 );
			}
		}
	}

	graph.spfa(1);

	printf( "%d %d\n", n, m );
	for( int i = 1; i <= pre[0].ecnt; i ++ ) {
		int o = pre[0].get_from(i), to = pre[0].get_to(i);
		if( vis[o] && vis[to] ) {
			printf( "%d %d %d\n", o, to, graph.dis[to] - graph.dis[o] );
		}
		else {
			printf( "%d %d %d\n", o, to, 1 );
		}
	}
}
