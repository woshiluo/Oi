#include <cstdio>

#include <vector>
#include <algorithm>

const int N = 1100;

int n, m, ans_cnt; 
int f[N][N], degree[N];

std::vector<int> ans[N];
int st[N];

void dfs( int cur, int ans_id ) {
	for( int &i = st[cur]; i <= n; i ++ ) {
		if( f[cur][i] ) {
			f[cur][i] = false;
			f[i][cur] = false;
			if( ans_id == 0 ) 
				ans_id = ( ++ ans_cnt );
			ans[ans_id].push_back(i);
			dfs( i, ans_id );
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "domino.in", "r", stdin );
	freopen( "domino.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	n ++;
	for( int i = 1; i <= n; i ++ ) {
		st[i] = 1;
		degree[i] = n - 1;
		for( int j = 1; j <= n; j ++ ) {
			f[i][j] = true;
		}
	}
	for( int i = 1; i <= m; i ++  ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		u ++, v ++;
		f[u][v] = f[v][u] = false;
		degree[u] --, degree[v] --;
	}
	for( int i = 1; i <= n; i ++ ) {
		if( degree[i] % 2 == 1 ) {
			if( ans[ans_cnt + 1].size() != 0 )
				ans[ans_cnt + 1][0] = i;
			else
				ans[ ans_cnt + 1 ].push_back(i);
			dfs( i, 0 );
		}
	}
	printf( "%d\n", ans_cnt );
	for( int i = 1; i <= ans_cnt; i ++ ) {
		int size = ans[i].size();
		for( int j = 0; j < size; j ++ ) {
			printf( "%d ", ans[i][j] - 1 );
		}
		printf( "-1\n" );
	}
}
