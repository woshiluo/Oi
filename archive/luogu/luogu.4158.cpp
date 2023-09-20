#include <cstdio>
#include <cstring>

#include <algorithm>

inline void chk_Min( int &a, int b ) { a = std::min( a, b ); }
inline void chk_Max( int &a, int b ) { a = std::max( a, b ); }
inline int len( int left, int rig ) { 
	if( rig < left ) 
		return 0;
	return rig - left + 1; 
}

const int N = 110;
const int T = 2600;
const int INF = 0x3f3f3f3f;

int n, m, t;
int mp[N][N], val[N][N], f[T][T];

int main() {
#ifdef woshiluo
	freopen( "luogu.4158.in", "r", stdin );
	freopen( "luogu.4158.out", "w", stdout );
#endif

	scanf( "%d%d%d", &n, &m, &t );
	for( int i = 1; i <= n; i ++  ){
		for( int j = 1; j <= m; j ++ ) {
			scanf( "%1d", &mp[i][j] );
		}
	}

	// FIXME: Is this right?
	//memset( val, INF, sizeof(val) );
	for( int o = 1; o <= n; o ++ ) {
		int f[N][N], sum[N];
		// FIXME: Is this right?
		memset( f, INF, sizeof(f) );
		memset( sum, 0, sizeof(sum) );
		for( int i = 1; i <= m; i ++ ) {
			sum[i] = sum[ i - 1 ] + mp[o][i];
		}
		f[0][0] = 0;
		for( int i = 1; i <= m; i ++ ) {
			f[i][0] = f[ i - 1 ][0];
			for( int k = 1; k <= m; k ++ ) { 
				for( int j = 0; j < i; j ++ ) {
					if( f[j][ k - 1 ] == INF ) 
						continue;
					if( f[i][k] == INF )
						f[i][k] = 0;
					chk_Max( f[i][k], f[j][ k - 1 ] + 
							std::max( sum[i] - sum[j], len( j + 1, i ) - ( sum[i] - sum[j] ) ) );
				}
			}
		}

		for( int i = 1; i <= m; i ++ ) {
			val[o][i] = std::max( val[o][ i - 1 ], f[m][i] );
		}
	}

	int ans = 0;
	int f[N][T];
	memset( f, INF, sizeof(f) );
	f[0][0] = 0;
	for( int i = 1; i <= n; i ++ ) {
		f[i][0] = f[ i - 1 ][0];
		for( int j = 1; j <= t; j ++ ) {
			for( int k = 0; k <= m; k ++ ) {
				if( j - k < 0 || f[ i - 1 ][ j - k ] == INF ) 
					continue;
				if( f[i][j] == INF ) 
					f[i][j] = 0;
				chk_Max( f[i][j], f[ i - 1 ][ j - k ] + val[i][k] );
				chk_Max( ans, f[i][j] );
			}
		}
	}

	printf( "%d\n", ans );
}
