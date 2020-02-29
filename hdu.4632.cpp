#include <cstdio>
#include <cstring>


const int N = 1100;
const int mod = 10007;

inline int add( int a, int b ) { return ( ( ( a + b ) % mod ) + mod ) % mod; }

int T, n;
char s[N];
int f[N][N];

inline void init() {
	memset( f, 0, sizeof(f) );
}

void readin() {
	scanf( "%s", s + 1 );
	n = strlen( s + 1 );
}

void dp() { 
	for( int i = 1; i <= n; i ++ ) 
		f[i][i] = 1;
	for( int len = 2; len <= n; len ++ ) {
		for( int left = 1, rig = len; rig <= n; left ++, rig ++ ) {
			if( s[left] == s[rig] ) 
				f[left][rig] = add( f[left][rig], add( f[ left + 1 ][ rig - 1 ], 1 ) );
			f[left][rig] = add( f[left][rig], add( f[left][ rig - 1 ], add( f[ left + 1 ][rig], - f[ left + 1 ][ rig - 1 ] ) ) );
		}
	}
}

int main() {
#ifdef woshiluo 
	freopen( "hdu.4632.in", "r", stdin );
	freopen( "hdu.4632.out", "w", stdout );
#endif
	scanf( "%d", &T );
	for( int i = 1; i <= T; i ++ ) {
		init();
		readin();
		dp();
		printf( "Case %d: %d\n", i, f[1][n] );
	}
}
