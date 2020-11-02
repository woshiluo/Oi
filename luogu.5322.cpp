#include <cstdio>
#include <cstring>

#include <algorithm>

const int M = 21000;
const int INF = 0x3f3f3f3f;

int s, n, m;
int a[110][110];
int f[110][M];

int main() {
#ifdef woshiluo
	freopen( "luogu.5322.in", "r", stdin );
	freopen( "luogu.5322.out", "w", stdout );
#endif
	scanf( "%d%d%d", &s, &n, &m );
	// memset( f, -1, sizeof(f) );
	// f[0][0] = 0;
	for( int i = 1; i <= s; i ++ ) { 
		for( int j = 1, tmp; j <= n; j ++ ) {
			scanf( "%d", &tmp );
			a[j][i] = ( 2 * tmp ) + 1;
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		std::sort( a[i] + 1, a[i] + s + 1 );
		for( int k = 0; k <= m; k ++ ) {
			f[i][k] = f[ i - 1 ][k];
		}
		for( int j = 1; j <= s; j ++ ) {
			for( int k = m; k >= a[i][j]; k -- ) {
				f[i][k] = std::max( f[ i - 1 ][ k - a[i][j] ] + i * j, f[i][k] );
			}
		}
	}
	printf( "%d\n", f[n][m] );
}
