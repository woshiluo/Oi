#include <cstdio>
#include <cstring>

inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 110;
const int INF = 0x3f3f3f3f;

int n;
char a[N], b[N];
int f[N][N], g[N];

inline void init() {
	memset( f, 0, sizeof(f) );
	memset( g, 0, sizeof(g) );
	n = strlen( a + 1 );
}

inline void dp() {
	for( int i = 1; i <= n; i ++ ) {
		f[i][i] = 1;
	}
	for( int len = 2; len <= n; len ++ ) {
		for( int left = 1, rig = len; rig <= n; left ++, rig ++ ) {
			f[left][rig] = INF;
			f[left][rig] = Min( f[left][rig], Min( Min( f[left][ rig - 1 ] + ( b[ rig - 1 ] != b[rig] ),
					f[left][ rig - 1 ] + ( b[left] != b[rig] ) ),
					Min( f[ left + 1 ][rig] + ( b[ left + 1 ] != b[left] ),
					f[ left + 1 ][rig] + ( b[left] != b[rig] ) ) ) );
			for( int mid = left; mid < rig; mid ++ ) {
				f[left][rig] = Min( f[left][rig], f[left][mid] + f[ mid + 1 ][rig] );
			}
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		g[i] = INF;
		if( a[i] == b[i] ) 
			g[i] = g[ i - 1 ];
		for( int j = 0; j < i; j ++ ) {
			g[i] = Min( g[i], g[j] + f[ j + 1 ][i] );
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "hdu.2476.in", "r", stdin );
	freopen( "hdu.2476.out", "w", stdout );
#endif
	while( scanf( "%s", a + 1 ) != EOF ) {
		scanf( "%s", b + 1 );
		init(), dp();
		printf( "%d\n", g[n] );
	}
}
