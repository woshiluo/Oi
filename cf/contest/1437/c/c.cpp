// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/27 23:08:01 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
T aabs( T a ) { return a < 0? -a: a; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 210;
const int INF = 0x3f3f3f3f;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		int t[N];
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &t[i] );
		}
		std::sort( t + 1, t + n + 1 );

		int f[ N + N ][N];
		memset( f, INF, sizeof(f) );
		f[0][0] = 0;
		int ans = INF;
		for( int i = 1; i <= n + n; i ++ ) {
			f[i][0] = 0;
			for( int j = 1; j <= n; j ++ ) {
				if( f[ i - 1 ][ j - 1 ] == INF )
					f[i][j] = f[ i - 1 ][j];
				else {
					f[i][j] = Min( f[ i - 1 ][j], f[ i - 1 ][ j - 1 ] + aabs( i - t[j] ) );
					if( j == n ) 
						chk_Min( ans, f[i][j] );
				}
			}
		}
		printf( "%d\n", ans );
	}
}
