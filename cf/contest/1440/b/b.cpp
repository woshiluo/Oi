// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/17 22:45:41 
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

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n, k;
		scanf( "%d%d", &n, &k );
		int fir = ( n % 2 == 0 )? ( n / 2 ) - 1: ( n / 2 );
		long long ans = 0;
		for( int i = 1, tmp; i <= fir * k; i ++ ) 
			scanf( "%d", &tmp );
		for( int i = 1; i <= k; i ++ ) {
			for( int j = 1; j <= n - fir; j ++ ) {
				int tmp;
				scanf( "%d", &tmp );
				if( j == 1 ) 
					ans += tmp;
			}
		}
		printf( "%lld\n", ans );
	}
}
