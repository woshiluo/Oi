#include <cstdio>
#include <vector>

const int N = 1e5 + 1e4;

int a[N], col[N], ans[N], offset[N], cur_p;
bool vis[N];
std::vector<int> p[N];

void dfs( int cur ) {
	vis[cur] = true;
	col[cur] = cur_p;
	p[cur_p].push_back(cur);
	if( vis[ a[cur] ] ) 
		return ;
	offset[ a[cur] ] = offset[cur] + 1;
	dfs( a[cur] );
}

int main() {
#ifdef woshiluo
	freopen( "luogu.5151.in", "r", stdin );
	freopen( "luogu.5151.out", "w", stdout );
#endif
	int n, k;
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}

	for( int i = 1; i <= n; i++ ) {
		if( !vis[ i ] ) {
			cur_p ++;
			dfs( i );
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		int mod = ( p[ col[i] ].size() );
		ans[ p[ col[i] ][ ( ( offset[i] + ( k % mod ) ) + mod ) % mod ] ] = i;
	}

	for( int i = 1; i <= n; i ++ ) 
		printf( "%d ", ans[i] );
}
