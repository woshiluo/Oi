#include <cstdio>
#include <cstring>

inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 15;
const int INF = 0x3f3f3f3f;

int n, m, ans;
int bit[N], f[N][N], dp[ 100000 ][N];

int bit3( int cur, int pos ) {
	while( pos ) {
		cur /= 3;
		pos --;
	}
	return cur % 3;
}

void init() {
	ans = INF;
	memset( f, 0x3f, sizeof(f) );
	memset( dp, 0x3f, sizeof(dp) );
}

void readin() {
	for( int i = 1, u, v, w; i <= m; i ++ ) {
		scanf( "%d%d%d", &u, &v, &w );
		f[u][v] = f[v][u] = Min( f[u][v], w );
	}
}

void solve() {
	for( int i = 0; i <= n; i ++ ) {
		dp[ bit[i] ][ i + 1 ] = 0;
	}
	for( int k = 0; k < bit[n]; k ++ ) {
		bool flag = false;
		for( int i = 1; i <= n; i ++) {
			int cur = bit3( k, i - 1 );
			if( cur == 2 ) 
				continue;
			if( cur == 0 ) 
				flag = true;
			for( int j = 1; j <= n && k + bit[ i - 1 ] < bit[n]; j ++ ) {
				dp[ k + bit[ i - 1 ] ][i] = Min( dp[ k + bit[ i - 1 ] ][i], dp[k][j] + f[i][j] );
			}
		}
		if( flag == false ) {
			for( int i = 1; i <= n; i ++ ) 
				ans = Min( ans, dp[k][i] );
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "hdu.3001.in", "r", stdin );
	freopen( "hdu.3001.out", "w", stdout );
#endif
	bit[0] = 1;
	for( int i = 1; i <= 15; i ++ ) 
		bit[i] = bit[ i - 1 ] * 3;
	while( scanf( "%d%d", &n, &m ) != EOF ) {
		init();
		readin();
		solve();
		printf( "%d\n", ans );
	}
}
