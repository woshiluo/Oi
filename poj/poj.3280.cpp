#include <cstdio>
#include <cstring>

inline int Min( int a, int b ) { return a < b? a: b; }

const int M = 2100;
const int N = 30;
const int INF = 0x3f3f3f3f;

int n, m;
char s[M];
int mon[210];
int f[M][M];

int main() {
#ifdef woshiluo 
	freopen( "poj.3280.in", "r", stdin );
	freopen( "poj.3280.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	scanf( "%s", s + 1 );
	for( int i = 1, b, c; i <= n; i ++ ) {
		char a[3];
		scanf( "%s", a );
		scanf( "%d%d", &b, &c );
		mon[ a[0] ] = Min( b, c );
	}

	memset( f, 0, sizeof(f) );
	for( int len = 2; len <= m; len ++ ) {
		for( int left = 1, rig = len; rig <= m; left ++, rig ++ ) {
			f[left][rig] = INF;
			if( s[left] == s[rig] ) 
				f[left][rig] = Min( f[left][rig], f[ left + 1 ][ rig - 1 ] );
			f[left][rig] = Min( f[left][rig], f[left][ rig - 1 ] + mon[ s[rig] ] );
			f[left][rig] = Min( f[left][rig], f[ left + 1 ][rig] + mon[ s[left] ] );
		}
	}

	printf( "%d\n", f[1][m] );
}
