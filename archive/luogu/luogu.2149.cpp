#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>

const int N = 1505;
const int M = N * N;
const int INF = 0x3f3f3f3f;

int n, m;

struct Graph {
	struct Edge {
		int from, to, val, next;
	};
	std::vector<Edge> e;
	int ehead[N], ecnt;
	inline void add_edge( int cur, int to, int val ) {
		ecnt ++;
		e.push_back( (Edge) { 0, 0, 0, 0 } );
		e[ecnt].to = to;
		e[ecnt].val = val;
		e[ecnt].from = cur;
		e[ecnt].next = ehead[cur];
		ehead[cur] = ecnt;
	}
	Graph() {
		e.push_back( (Edge) { 0, 0, 0, 0 } );
		memset( ehead, 0, sizeof(ehead) );
		ecnt = 0;
	}


	struct DijNode {
		int pos, dis;
		bool operator< ( const DijNode &b ) const {
			return dis > b.dis;
		}
	};
	std::vector<int> dij( int st ) {
		std::priority_queue<DijNode> q;
		std::vector<int> dis; std::vector<bool> vis;
		dis.resize(N, INF); vis.resize(N, 0);

		dis[st] = 0;
		q.push( (DijNode) { st, 0 } );
		while( !q.empty() ) {
			DijNode cur = q.top(); q.pop();
			int pos = cur.pos;
			if( vis[pos] ) 
				continue;
			vis[pos] = true; 
			for( int i = ehead[pos]; i; i = e[i].next ) {
				int to = e[i].to;
				if( dis[pos] + e[i].val < dis[to] ) {
					dis[to] = dis[pos] + e[i].val;
					if( !vis[to] ) {
						q.push( { to, dis[to] } );
					}
				}
			}
		}

		return dis;
	}

	int topu_find( int st, int from, int end, std::vector<int> from_dis, std::vector<int> to_dis ) {
		std::queue<int> q;
		static int in_degree[N], dis[N], len[N];
		int res = 0;

		memset( in_degree, 0, sizeof(in_degree) );
		memset( len, 0, sizeof(len) );
		memset( dis, INF, sizeof(dis) );
		dis[st] = len[st] = 0;

		for( int i = 1; i <= ecnt; i ++ ) 
			in_degree[ e[i].to ] ++;
		for( int i = 1; i <= n; i ++ ) 
			if( in_degree[i] == 0 )
				q.push(i);

		while( !q.empty() ) {
			int cur = q.front(); q.pop();
			if( from_dis[st] + to_dis[cur] + dis[cur] == from_dis[end] ) 
				res = std::max( res, dis[cur] );
			for( int i = ehead[cur]; i; i = e[i].next ) {
				int to = e[i].to;
				if( dis[cur] + e[i].val <= dis[to] ) {
					dis[to] = dis[cur] + e[i].val;
					if( len[cur] + 1 > len[to] )
						len[to] = len[cur] + 1;
				}
				in_degree[to] --;
				if( in_degree[to] == 0 ) 
					q.push(to);
			}
		}

		return res;
	}
	int find( int from, int to, std::vector<int> from_dis, std::vector<int> to_dis ) {
		int res = 0;
		for( int i = 1; i <= n; i ++ ) {
			res = std::max( res, topu_find( i, from, to, from_dis, to_dis ) );
		}
		return res;
	}
};

int main() {
#ifdef woshiluo
	freopen( "luogu.2149.in", "r", stdin );
	freopen( "luogu.2149.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	int x1, y1, x2, y2;
	scanf( "%d%d%d%d", &x1, &y1, &x2, &y2 );
	Graph ori, sub, rev_sub;
	for( int i = 1; i <= m; i ++ ) {
		int u, v, w;
		scanf( "%d%d%d", &u, &v, &w );
		ori.add_edge( u, v, w );
		ori.add_edge( v, u, w );
	}

	std::vector<int> ela_dis = ori.dij(x1);
	std::vector<int> wxx_dis = ori.dij(x2);
	std::vector<int> lab_dis = ori.dij(y2);

	{
		bool vis[N];
		std::queue<int> q;

		memset( vis, 0, sizeof(vis) );
		vis[y1] = true; q.push(y1);

		while( !q.empty() ) {
			int cur = q.front(); q.pop();
			for( int i = ori.ehead[cur]; i; i = ori.e[i].next ) {
				int to = ori.e[i].to, val = ori.e[i].val;
				if( ela_dis[to] + val == ela_dis[cur] ) {
					sub.add_edge( to, cur, val );
					rev_sub.add_edge( cur, to, val );

					if( !vis[to] ) {
						vis[to] = true;
						q.push( to );
					}
				}
			}
		}
	}

	printf( "%d\n", std::max( sub.find( x2, y2, wxx_dis, lab_dis ), 
				rev_sub.find( x2, y2, wxx_dis, lab_dis ) ) );
}
