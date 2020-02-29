#include <cstdio>

#include <algorithm>

inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 1e5 + 1e4;
const int INF = 0x7fffffff;

int T, n, x;
int a[N];

int main() {
#ifdef woshiluo
	freopen( "B.in", "r", stdin );
	freopen( "B.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		int ans = INF;
		scanf( "%d%d", &n, &x );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			if( a[i] == x ) 
				ans = Min( ans, 1 );
		}
		std::sort( a + 1, a + n + 1 );
		int tmp = x / 2 + ( x & 1 );
		if( a[n] >= tmp ) 
			ans = Min( ans, 2 );
		else 
			ans = Min( ans, ( x / a[n] ) + ( ( x % a[n] ) != 0 ) );
		printf( "%d\n", ans );
	}
}
