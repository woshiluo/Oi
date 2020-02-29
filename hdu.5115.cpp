#include <cstdio>
#include <cstring>

inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 210;
const int INF = 0x3f3f3f3f;

int T, _case;
int n;
int a[N], b[N], f[N][N];

void init() {
	memset( f, 0, sizeof(f) );
}

void dp() {
	for( int len = 1; len <= n; len ++ ) {
		for( int left = 1, rig = len; rig <= n; left ++, rig ++ ) {
			f[left][rig] = INF;
			for( int mid = left; mid <= rig; mid ++ ) {
				f[left][rig] = Min( f[left][rig], f[left][mid - 1] + f[ mid + 1 ][rig] + a[mid] + b[ left - 1 ] + b[ rig + 1 ] );
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "hdu.5115.in", "r", stdin );
	freopen( "hdu.5115.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &b[i] );
		}
		init(); dp();
		printf( "Case #%d: %d\n", ++_case, f[1][n] );
	}
}
