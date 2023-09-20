#include <cstdio>

const int N = 1e5 + 1e4;
const long long INF = ( 1LL << 62 );

int n, k;
long long ans = INF;
int a[N];
long long sum[N], que[N], max[N], re_max[N];

inline long long Max( long long a, long long b ) { return a > b? a: b; }
inline long long Min( long long a, long long b ) { return a < b? a: b; }

int main() {
	freopen( "prizes.in", "r", stdin );
	freopen( "prizes.out", "w", stdout );

	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		sum[i] = sum[ i - 1 ] + (long long)a[i];
	}
	for( int left = 1, rig = k; rig <= n; left ++, rig ++ ) {
		que[left] = sum[rig] - sum[ left - 1 ];
	}
	for( int i = 1; i <= n; i ++ ) {
		max[i] = Max( que[i], max[ i - 1 ] );
	}
	for( int i = n; i >= 1; i -- ) {
		re_max[i] = Max( que[i], re_max[ i + 1 ] );
	}

	for( int left = 1, rig = k; rig <= n; left ++, rig ++ ) {
		ans = Min( ans, Max( max[ Max( left - k, 0LL ) ], re_max[ rig + 1 ] ) );
	}

	printf( "%lld\n", ans );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
