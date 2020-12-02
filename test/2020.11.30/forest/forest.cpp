#include <cstdio>
#include <cstring>

#include <queue>

inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 2100;
const int INF = 0x3f3f3f3f;

int n, m;
bool mp[N][N];
int dis[N][N];

int dx[8] = { +1, +1, +1, +0, +0, -1, -1, -1 };
int dy[8] = { +1, +0, -1, +1, -1, +1, +0, -1 };

struct node {
	int x, y;
} wall, st;

inline bool chk( node cur ) {
	return ( cur.x >= 1 && cur.x <= n && cur.y >= 1 && cur.y <= m && mp[cur.x][cur.y] );
}

void bfs() {
	std::queue<node> q;
	q.push(st);
	memset( dis, INF, sizeof(dis) );
	dis[ st.x ][ st.y ] = 0;
	while( !q.empty() ) {
		node cur = q.front(); q.pop();
		for( int i = 0; i < 8; i ++ ) {
			node tmp = cur;
			tmp.x += dx[i]; tmp.y += dy[i];
			if( chk(tmp) ) {
				if( dis[ tmp.x ][ tmp.y ] > dis[ cur.x ][ cur.y ] + 1 ) {
					dis[ tmp.x ][ tmp.y ] = dis[ cur.x ][ cur.y ] + 1;
					q.push(tmp);
				}
			}
		}
	}
}

int main() {
	freopen( "forest.in", "r", stdin );
	freopen( "forest.out", "w", stdout );

	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ ){
		static char str[N];
		scanf( "%s", str + 1 );
		for( int j = 1; j <= m; j ++ ) {
			mp[i][j] = ( str[j] != 'X' );
			if( str[j] == '*' ) 
				st = (node) { i, j };
			if( mp[i][j] == false && wall.x == 0 )
				wall = (node) { i, j };
		}
	}

	for( int i = 1; i < wall.x; i ++ ) {
		mp[i][ wall.y ] = 0;
	}
	bfs();

	int ans = INF;
	for( int i = 1; i < wall.x; i ++ ) {
		ans = Min( ans, Min( dis[i][ wall.y - 1 ], Min( dis[i + 1][ wall.y - 1 ], dis[i - 1][ wall.y - 1 ] ) ) + 
				Min( dis[i][ wall.y + 1 ], Min( dis[i + 1][ wall.y + 1 ], dis[i - 1][ wall.y + 1 ] ) ) + 2 );
	}
	printf( "%d\n", ans );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
