// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/11 17:23:00 
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

const int N = 2e5 + 1e4;

int T;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		int n, k;
		int a[N];
		scanf( "%d%d", &n, &k );
		for( int i = 1; i <= n; i ++ ) 
			scanf( "%d", &a[i] );

		std::sort( a + 1, a + n + 1 );
		// int p1 = 1;
		long long ans = a[n];
		for( int i = n - 1; i >= 1 && k > 0; i --, k -- ) {
			ans += a[i];
		}
		printf( "%lld\n", ans );
	}
}
