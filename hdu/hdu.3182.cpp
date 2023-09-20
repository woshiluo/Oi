#include <cstdio>

#include <cstring>

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 20;
const int N_2 = 1 << 20;

int T, n, E, ans;
int mon[N], val[N];
int bit[N + 1], right[N];
int f[ N_2 ][2];

inline bool allow( int zip, int cur ) { return ( ( right[cur] & zip ) == right[cur] ); }

void init() { ans = 0; memset( f, -1, sizeof(f) ); memset( right, 0, sizeof(right) ); }

void work() {
	scanf( "%d%d", &n, &E );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &val[i] );
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &mon[i] );
	}
	for( int i = 1, tmp_n, tmp; i <= n; i ++ ) {
		scanf( "%d", &tmp_n );
		for( int j = 1; j <= tmp_n; j ++ ) {
			scanf( "%d", &tmp );
			right[i] |= bit[ tmp - 1 ];
		}
	}
	f[0][0] = 0, f[0][1] = 0;
	for( int zip = 0; zip < bit[n]; zip ++ ) {
		if( f[zip][1] == -1 ) 
			continue;
		for( int i = 1; i <= n; i ++ ) {
			if( ( zip >> ( i - 1 ) ) & 1 || f[zip][0] + mon[i] > E || ( ! allow( zip, i ) ) )
				continue;
			int next_zip = ( zip | ( bit[ i - 1 ] ) );
			if( f[zip][1] + val[i] > f[next_zip][1] ) {
				f[next_zip][0] = f[zip][0] + mon[i];
				f[next_zip][1] = f[zip][1] + val[i];
				ans = Max( ans, f[next_zip][1] );
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "hdu.3182.in", "r", stdin );
	freopen( "hdu.3182.out", "w", stdout );
#endif
	scanf( "%d", &T );
	bit[0] = 1;
	for( int i = 1; i <= 20; i ++ ) {
		bit[i] = bit[ i - 1 ] * 2;
	}
	for( int i = 1; i <= T; i ++ ) {
		init();
		work();
		printf( "%d\n", ans );
	}
}
