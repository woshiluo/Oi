#include <cstdio>
#include <cstring>

inline int Max( int a, int b ) { return a > b? a: b; }
inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 5100;

int n;
int a[N];
int f[N][N][5];

int main() {
#ifdef woshiluo
	freopen( "loj.2813.in", "r", stdin );
	freopen( "loj.2813.out", "w", stdout );
#endif
	scanf( "%d", &n );
	memset( f, 0x3f, sizeof(f) );
	f[0][0][2] = f[0][0][4] = 0;
	for( int i = 1; i <= n; i ++ ) 
		scanf( "%d", &a[i] );

	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j <= n; j ++ ) {
			int lst = Max( 0, a[i] - a[ i - 1 ] + 1 ), 
				nxt = Max( 0, a[i] - a[ i + 1 ] + 1 );
			f[i][j][0] = f[ i - 1 ][j][1] + lst;
			f[i][j][1] = Min( f[ i - 1 ][ j -  1 ][3], f[ i - 1 ][ j - 1 ][2] );
			f[i][j][4] = Min( f[ i - 1 ][j][0], f[ i - 1 ][j][4] );
			f[i][j][2] = f[i][j][4] + nxt;
			f[i][j][3] = f[ i - 1 ][j][1] + Max( 0,
					a[i] - Min( a[ i - 1 ], a[ i + 1 ] ) + 1 );
		}
	}
	for( int i = 1; i <= n / 2 + ( n & 1 ); i ++ ) {
		printf( "%d ",
				Min( f[n][i][0], Min( f[n][i][1], f[n][i][4] ) ) );
	}
}
