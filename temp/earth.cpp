#include <cstdio>
#include <cstring>

#include <queue>

const int N = 110;
const int INF = 0x3f3f3f3f;

int T, n, m;
int mid;
bool f[N][N];

// Edge Start 
struct edge {
	int to, next, val;
} e[N];
int ehead[ N * N ], ecnt;
inline void add_edge( int now, int to, int val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

int dis[N];
bool vis[N];
int cnt[N];
void spfa( int st ) {
	memset( dis, INF, sizeof(dis) );
	memset( vis, 0, sizeof(vis) );
	memset( cnt, 0, sizeof(cnt) );
	std::queue<int> q;
	vis[st] = true; dis[st] = 0;
	q.push(st);
	while( !q.empty() ) {
		int cur = q.front();
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( dis[ e[i].to ] > dis[cur] + e[i].val + mid ) {
				dis[ e[i].to ] = dis[cur] + e[i].val + mid;
				if( vis[ e[i].to ] == false ) {
					vis[ e[i].to ] = true;
					q.push( e[i].to );
					cnt[ e[i].to ] ++;
					if( cnt[ e[i].to ] > n ) {
						dis[n] = -INF;
						return ;
					}
				}
			}
		}
		vis[cur] = false;
		q.pop();
	}
}

int main() {
	freopen( "earth.in", "r", stdin );
	freopen( "earth.out", "w", stdout );

	scanf( "%d", &T );
	while( T -- ) {
		ecnt = 0;
		memset( ehead, 0, sizeof(ehead) );
		memset( f, 0, sizeof(f) );
		mid = 0;
		int left = 0, rig = 110000, res = 0;
		scanf( "%d%d", &n, &m );
		for( int i = 1, u, v, w; i <= m; i ++ ) {
			scanf( "%d%d%d", &u, &v, &w );
			add_edge( u, v, w );
			f[u][v] = 1;
			if( w < left )
				left = w;
		}
		for( int i = 1; i <= n; i ++ ) {
			f[i][i] = 1;
		}
		for( int k = 1; k <= n; k ++ ) {
			for( int i = 1; i <= n; i ++ ) {
				for( int j = 1; j <= n; j ++ ) {
					f[i][j] = ( f[i][j] || ( f[i][k] && f[k][j] ) );
				}
			}
		}
		if( f[1][n] == false ) {
			printf( "-1\n" );
			continue;
		}
		if( left > 0 )
			left = -left;
		while( left <= rig ) {
			mid = ( left + rig ) >> 1;
			spfa(1);
			if( dis[n] >= 0 ) {
				res = mid;
				rig = mid - 1;
			}
			else
				left = mid + 1;
		}
		spfa(res); 
		printf( "%d\n", dis[n] );
	}
}
