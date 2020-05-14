// Woshiluo<woshiluo@woshiluo.site>
// Started at 2020-04-10 23:17
// Blog: https://blog.woshiluo.com
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

template<class T> 
T Min( T a, T b ) { return a < b? a: b; }
template<class T> 
T Max( T a, T b ) { return a > b? a: b; }
template<class T> 
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T> 
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

const int N = 1e6 + 1e5;
const long long INF = ( 1LL << 60 );

int T;
int n;
long long a[N], b[N], sum[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		long long ans = INF;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%lld%lld", &a[i], &b[i] );
		}
		for( int i = 1; i <= n; i ++ ) {
			a[ i + n ] = a[i]; b[ i + n ] = b[i];
		}
		int n_2 = 2 * n;
		for( int i = 1; i <= n_2; i ++ ) {
			sum[i] = sum[ i - 1 ] + Max( 0LL, a[i] - b[ i - 1 ] );
		}
		for( int i = 1; i <= n; i ++ ) {
			long long res = a[i] + sum[ i + n - 1 ] - sum[i];
			chk_Min( ans, res );
		}
		printf( "%lld\n", ans );
	}
}
