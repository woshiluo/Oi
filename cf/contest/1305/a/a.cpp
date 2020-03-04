#include <cstdio>
#include <cstring>

#include <algorithm>

const int N = 110;

int t;
int n;
int a[N], b[N];

int main() {
#ifdef woshiluo
	freopen( "A.in", "r", stdin );
	freopen( "A.out", "w", stdout );
#endif
	scanf( "%d", &t );
	while( t -- ) {
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ )
			scanf( "%d", &a[i] );
		for( int i = 1; i <= n; i ++ ) 
			scanf( "%d", &b[i] );
		
		std::sort( a + 1, a + n + 1 );
		std::sort( b + 1, b + n + 1 );

		for( int i = 1; i <= n; i ++ ) 
			printf( "%d ", a[i] );
		printf( "\n" );
		for( int i = 1; i <= n; i ++ ) 
			printf( "%d ", b[i] );
		printf( "\n" );
	}
}
