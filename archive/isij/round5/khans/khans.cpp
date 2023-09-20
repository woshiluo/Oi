#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 11;
const int MAX_TIME = 2e7 + 1e6;

int n, m, k, ans, res;
int mp[N][N];

inline bool check( int x, int y ) {
	if( x < 1 || y < 1 || x > n || y > m ) 
		return false;
	return true; 
}

inline int ask( int cur ) {
	if( cur > 8 ) 
		return 128;
	return 1 << ( cur - 2 );
}

struct node {
	int x, y, val;
	int vis[N][N];
	node( int _x, int _y, int _val ) {
		memset( vis, 0, sizeof(vis) );
		x = _x, y = _y;
		vis[x][y] = 1;
		val = _val;
	}
};

bool cmp( node _a, node _b ) {
	return _a.val > _b.val;
}

int dx[4] = { +1, -1, 0, 0 };
int dy[4] = { 0, 0, +1, -1 };

int main() {
#ifdef woshiluo
	freopen( "khans.in", "r", stdin );
	freopen( "khans.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &k );

	for( int i = 1; i <= n; i ++ ) { 
		for( int j = 1; j <= m; j ++ ) {
			scanf( "%d", &mp[i][j] );
		}
	}

	std::vector<node> q[2];
	int cur = 0, nxt = 1;
	q[cur].push_back( node( 1, 1, mp[1][1] ) );
	for( int o = 2; o <= k; o ++ ) {
		q[nxt].clear();
		std::sort( q[cur].begin(), q[cur].end(), cmp );
		int size = q[cur].size();
		for( int j = 0; j < 2150; j ++ ) {
			if( j >= size ) 
				break;
			node &top = q[cur][j];
			for( int i = 0; i < 4; i ++ ) {
				node tmp = top;
				tmp.x += dx[i];
				tmp.y += dy[i];

				if( check( tmp.x, tmp.y ) == false ) 
					continue;
				int tmp_vis = top.vis[tmp.x][tmp.y];
				if( tmp_vis != 0 && ask( o - tmp_vis ) < mp[tmp.x][tmp.y] )
					continue;
				tmp.vis[tmp.x][tmp.y] = o;
				tmp.val += mp[tmp.x][tmp.y];
				ans = Max( ans, tmp.val );
				q[nxt].push_back(tmp);
			}
//			q[cur].pop();
		}
		cur ^= 1, nxt ^= 1;
	}

	printf( "%d\r\n", ans );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
