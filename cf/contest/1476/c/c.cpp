// Woshiluo<woshiluo@woshiluo.site>
// 2021/01/29 23:47:24 
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
template <class T> 
T aabs( T a ) { return a < 0? -a: a; }

const int N = 1e5 + 1e4;

int a[N], b[N], c[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &c[i] );
		}
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &b[i] );
		}

		long long cur = 0, ans = 0;
		for( int i = 1; i <= n; i ++ ) {
			if( i == 1 ) {
				cur += aabs( a[ i + 1 ] - b[ i + 1 ] );
				cur += 2;
			}
			else if( i == n ) {
				cur += c[n] - 1;
				chk_Max( ans, cur );
			}
			else if( a[ i + 1 ] == b[ i + 1 ] ) {
				chk_Max( ans, cur + c[i] - 1 );
				cur = 2;
			}
			else {
				chk_Max( ans, cur + c[i] - 1 );
				cur += c[i] - aabs( a[ i + 1 ] - b[ i + 1 ] ) - 1;
				chk_Max( cur, (long long)aabs( a[ i + 1 ] - b[ i + 1 ] ) );
				cur += 2;
			}
		}
		printf( "%lld\n", ans );
	}
}
