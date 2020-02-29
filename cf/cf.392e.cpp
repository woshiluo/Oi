#include <cstdio>
#include <cstring>

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 410;
const int INF = 0x3f3f3f3f;

int n;
int v[N], w[N];
int f[N][N], g[N][N], h[N][N], ans[N];
// g 1 -> 2 
// h 2 -> 1

int main() {
#ifdef woshiluo
	freopen( "cf.392e.in", "r", stdin );
	freopen( "cf.392e.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &v[i] );
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &w[i] );
	}

	for( int i = 1; i <= n; i ++ ) {
		f[i][i] = v[1];
		g[i][i] = h[i][i] =0;
	}

	for( int len = 2; len <= n; len ++ ) {
		for( int left = 1, rig = len; rig <= n; left ++, rig ++ ) {
			h[left][rig] = g[left][rig] = f[left][rig] = -INF;
			for( int mid = left + 1; mid <= rig; mid ++ ) {
				if( w[left] + 1 == w[mid] ) 
					g[left][rig] = Max( g[left][rig], f[ left + 1 ][ mid - 1 ] + g[mid][rig] );
				if( w[left] - 1 == w[mid] ) 
					h[left][rig] = Max( h[left][rig], f[ left + 1 ][ mid - 1 ] + h[mid][rig] );
				f[left][rig] = Max( f[left][rig], f[left][ mid - 1 ] + f[mid][rig] );
			}
			for( int mid = left; mid <= rig; mid ++ ) {
				int len = 2LL * w[mid] - w[left] - w[rig] + 1;
				if( 0 <= len && len <= n )
					f[left][rig] = Max( f[left][rig], g[left][mid] + h[mid][rig] + v[len] );
			}
		}
	}

	ans[0] = 0;
	for( int i = 1; i <= n; i ++ ) {
		ans[i] = ans[ i - 1 ];
		for( int j = 1; j <= i; j ++) {
			ans[i] = Max( ans[i], ans[ j - 1 ] + f[j][i] );
		}
	}

	printf( "%d\n", ans[n] );
}
