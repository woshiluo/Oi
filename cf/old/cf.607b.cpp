#include <cstdio>
#include <cstring>

const int N = 510;

inline int Min( int a, int b ) { return a < b? a: b; }

int n;
int a[N], f[N][N];

bool check( int left, int rig ) {
	while( left <= rig ) {
		if( a[left] != a[rig] )
			return false;
		left ++, rig --;
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "cf.607b.in", "r", stdin );
	freopen( "cf.607b.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}

	memset( f, 0x3f, sizeof(f) );
	for( int i = 1; i <= n; i ++ ) 
		f[i][i] = 1;

	for( int len = 2; len <= n; len ++ ) {
		for( int left = 1; left + len - 1 <= n; left ++ ) {
			int rig = left + len - 1;
			if( check( left, rig ) ) {
				f[left][rig] = 1;
				continue;
			}
			if( a[left] == a[rig] ) 
				f[left][rig] = Min( f[left][rig], f[ left + 1 ][ rig - 1 ] );
			for( int mid = left; mid < rig; mid ++ ) {
				f[left][rig] = Min( f[left][rig], f[left][mid] + f[ mid + 1 ][rig] );
			}
		}
	}

	printf( "%d\n", f[1][n] );
}
