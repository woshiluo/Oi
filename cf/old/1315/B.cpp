#include <cstdio>
#include <cstring>

const int N = 1e5 + 1e4;

int T;
int n, a, b, p;
long long cost[N];
char sta[N];

int main() {
#ifdef woshiluo
	freopen( "B.in", "r", stdin );
	freopen( "B.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		memset( cost, 0, sizeof( cost ) );
		scanf( "%d%d%d", &a, &b, &p );
		scanf( "%s", sta + 1 );
		n = strlen( sta + 1 );
		if( n == 1 ) {
			printf( "%d\n", 1 ) ;
			continue;
		}
		cost[n] = 0;
		cost[ n - 1 ] = ( sta[ n - 1 ] == 'A' )? a: b;
		for( int i = n - 2; i >= 1; i -- ) {
			cost[i] = cost[ i + 1 ];
			if( sta[i] != sta[ i + 1 ] ) 
				cost[i] += ( sta[i] == 'A' )? a: b;
		}
		for( int i = 1; i <= n; i ++ )  {
			if( cost[i] <= p ) {
				printf( "%d\n", i );
				break;
			}
		}
	}
}
