// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/29 22:42:28 
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
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 1e5 + 1e4;

int T;

int n, k, z;
int a[N], f[N][10];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d%d", &n, &k, &z );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}

		memset( f, 0, sizeof(f) );
		f[1][0] = a[1];
		for( int i = 2; i <= n; i ++ ) 
			f[i][0] = f[ i - 1 ][0] + a[i];
		for( int j = 1; j <= z; j ++ ) {
			for( int i = 1; i <= n; i ++ ) {
				f[i][j] = Max( f[ i + 1 ][ j - 1 ] + a[i], f[ i - 1 ][j] + a[i] );
			}
		} 

		int res = 0;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 0; j <= z; j ++ ) {
				if( i + j + j - 1 > k )
					break;
				res = Max( res, f[i][j] );
			}
		}
		printf( "%d\n", res );
	}
}
