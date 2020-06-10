#include <cstdio>

#include <queue>

const int N = 1600;
const int M = 1e5 + 1e4;

struct node { int x, y; };

int n, m;
int ans[M];
bool mp[N][N], vis[N][N];

bool chk( node cur ) {
	int x = cur.x, y = cur.y;
	if( x < 0 || y < 0 || x > n || y > m || mp[x][y] == false ) 
		return false;
	return true;
}
int dx[8] = { 1, 1, 1, 0, 0, -1, -1, -1 }; 
int dy[8] = { 1, 0, -1, 1, -1, 1, 0, -1 }; 

void bfs( int x, int y ) {
	vis[x][y] = true;
	std::queue<node> q;
	q.push( (node){ x, y } );
	int cnt = 1;
	while( !q.empty() ) {
		node cur = q.front(); q.pop();
		for( int i = 0; i < 8; i ++ ) {
			node nxt = cur;
			nxt.x += dx[i];
			nxt.y += dy[i];
			if( chk( nxt ) && vis[ nxt.x ][ nxt.y ] == false) {
				cnt ++;
				vis[nxt.x][nxt.y] = true;
				q.push( nxt );
			}
		}
	}
	ans[cnt] ++;
}

int main() {
	freopen( "star.in", "r", stdin );
	freopen( "star.out", "w", stdout );

	scanf( "%d%d", &n, &m );
	char str[N];
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%s", str );
		for( int j = 1; j <= m; j ++ ) {
			if( str[ j - 1 ] == '*' ) 
				mp[i][j] = true;
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			if( mp[i][j] && vis[i][j] == false ) 
				bfs( i, j );
		}
	}

	int cnt = 0;
	long long max = 0;
	for( int i = 1; i < M; i ++ ) {
		if( ans[i] != 0 ) {
			cnt ++;
			long long res = 1LL * ans[i] * i;
			if( res > max ) 
				max = res;
		}
	}
	printf( "%d %lld\n", cnt, max );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
