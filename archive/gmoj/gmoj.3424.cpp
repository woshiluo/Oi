#include <cstdio>
#include <cstring>

inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 910;
const int mod = 1000000007;

int T, n;
int a[N], s[N], c[N][N], f[N][N];

void init() {
	memset( f, 0, sizeof(f) );
}

void readin() {
	scanf( "%d", &n );
	for( int i = 1; i <= n; i++ ) {
		scanf( "%d", &a[i] );
		s[i] = s[ i - 1 ] + a[i];
	}
}

void work() {
	f[1][ s[1] - 1 ] = 1;
	for( int i = 1; i < n; i++ ) {
		for( int j = 0; j < s[i]; j++ ) {
			for( int k = 1; k <= a[ i + 1 ]; k++ ) {
				for( int l = 0; l <= Min( j, k ); l++ ) {
					f[ i + 1 ][ j + a[i + 1] - k - l ] =
						( f[ i + 1 ][ j + a[i + 1] - k - l ] +
						( ( ( ( ( 1LL * f[i][j] * c[ s[i] + 1 - j ][ k - l ] ) % mod ) * c[j][l] ) % mod ) * c[ a[i + 1] - 1 ][ k - 1 ] ) % mod ) % mod;
				}
			}
		}
	}
	printf( "%d\n", f[n][0] );
}

int main() {
#ifdef woshiluo
	freopen( "tmp.in", "r", stdin );
#endif
	c[1][1] = c[1][0] = 1;
	for( int i = 2; i < 905; i++ ) {
		for( int j = 0; j <= i; j++ ) {
			c[0][j] = 1;
			if( j == i || j == 0 )
				c[i][j] = 1;
			else
				c[i][j] = ( c[ i - 1 ][j] + c[ i - 1 ][ j - 1 ] ) % mod;
		}
	}
	scanf( "%d", &T );
	while( T -- ) {
		init();
		readin();
		work();
	}
}
