#include <cstdio>

inline int Max( int a, int b ) { return a > b? a: b; } 

const int N = 2100;

int n;
int v[N];
int f[N][N];

inline int len( int left, int rig ) { return rig - left + 1; }

int main() {
#ifdef woshiluo
	freopen( "luogu.2858.in", "r", stdin );
	freopen( "luogu.2858.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &v[i] );
		f[i][i] = v[i] * n;
	}
	for( int len = 2; len <= n; len ++ ) {
		for( int left = 1, rig = len; rig <= n; left ++, rig ++ ) {
			int cur = n - len( left, rig );
			f[left][rig] = Max( f[left][ rig - 1 ] + v[i] * cur, f[left + 1][rig] + v[i] * cur );
		}
	}
	printf( "%d", f[1][n] );
}
