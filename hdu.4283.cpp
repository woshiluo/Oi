#include <cstdio>
#include <cstring>

inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 110;
const int INF = 0x3f3f3f3f;

int T, n;
int a[N], sum[N];
int f[N][N];

inline void init() {
	memset( f, 0x3f, sizeof(f) );
	memset( f, 0, sizeof(f) );
	sum[0] = 0;
}

inline void readin() {
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		sum[i] = sum[ i - 1 ] + a[i];
	}
}

void dp() {
	for( int len = 2; len <= n; len ++ ) {
		for( int left = 1, rig = len; rig <= n; left ++, rig ++ ) {
			f[left][rig] = INF;
			for( int mid = left; mid <= rig; mid ++ ) {
				f[left][rig] = Min( f[left][rig], 
						a[left] * ( mid - left ) + ( sum[rig] - sum[mid] ) * ( mid - left + 1 ) + f[ left + 1 ][mid] + f[ mid + 1 ][rig] );
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "hdu.4283.in", "r", stdin );
	freopen( "hdu.4283.out", "w", stdout );
#endif
	scanf( "%d", &T );
	for( int i = 1; i <= T; i ++ ) {
		init();
		readin();
		dp();
		printf( "Case #%d: %d\n", i, f[1][n] );
	}
}
